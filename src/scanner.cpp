#include "scanner.h"
#include "hasher.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <vector>

namespace fs = std::filesystem;
const std::string BASELINE_FILE = ".sentinel-baseline";
const std::string LOG_FILE = ".sentinel.log";

// ANSI colors
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

// Default exclusions
const std::vector<std::string> EXCLUDE = {".git", "build"};

struct Event {
    std::string path;
    std::string status;
    uintmax_t size;
    std::string hash;
};

// Logging helper
void log_event(const std::string& event) {
    std::ofstream log(LOG_FILE, std::ios::app);
    if (!log) return;
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    log << "[" << std::put_time(std::localtime(&t_c), "%F %T") << "] " << event << "\n";
}

// HTML report helper
void write_html_report(const std::vector<Event>& events) {
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    std::ostringstream filename;
    filename << "sentinel_report_" << std::put_time(std::localtime(&t_c), "%Y%m%d_%H%M%S") << ".html";
    std::ofstream html(filename.str());
    if (!html) return;

    html << "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Sentinel-C Report</title>";
    html << "<style>body{font-family:Arial;}table{border-collapse:collapse;width:100%;}"
         << "th,td{border:1px solid #ccc;padding:8px;text-align:left;}"
         << ".NEW{background-color:#d4edda;}" 
         << ".MODIFIED{background-color:#fff3cd;}" 
         << ".DELETED{background-color:#f8d7da;}"
         << "</style></head><body>";
    html << "<h2>Sentinel-C Scan Report</h2>";
    html << "<p>Generated: " << std::put_time(std::localtime(&t_c), "%F %T") << "</p>";
    html << "<table><tr><th>File</th><th>Status</th><th>Size (bytes)</th><th>SHA-256</th></tr>";
    for (auto& e : events) {
        html << "<tr class='" << e.status << "'>"
             << "<td>" << e.path << "</td>"
             << "<td>" << e.status << "</td>"
             << "<td>" << e.size << "</td>"
             << "<td>" << e.hash << "</td></tr>";
    }
    html << "</table></body></html>";
    std::cout << "[+] HTML report generated: " << filename.str() << "\n";
}

// Exclusion check
static bool is_excluded(const fs::path& p) {
    for (const auto& ex : EXCLUDE)
        if (p.string().find(ex) != std::string::npos) return true;
    if (fs::is_symlink(p)) return true;
    return false;
}

// Scan directory
static std::vector<FileEntry> scan_directory(const std::string& root) {
    std::vector<FileEntry> files;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file() || is_excluded(entry.path())) continue;
        FileEntry fe;
        fe.path = entry.path().string();
        fe.size = entry.file_size();
        fe.hash = sha256_file(fe.path);
        files.push_back(fe);
    }
    return files;
}

// Initialize baseline
void initialize_baseline(const std::string& root) {
    auto files = scan_directory(root);
    std::ofstream out(BASELINE_FILE);
    std::cout << "[+] Creating baseline for: " << root << "\n";
    for (const auto& f : files) out << f.hash << "|" << f.size << "|" << f.path << "\n";
    std::cout << "[+] Baseline saved (" << files.size() << " files)\n";
    log_event("[+] Baseline created with " + std::to_string(files.size()) + " files");
}

// Scan and compare with HTML report
void scan_and_compare(const std::string& root) {
    std::ifstream in(BASELINE_FILE);
    if (!in) { std::cerr << "[-] No baseline found. Run init first.\n"; return; }

    std::unordered_map<std::string, FileEntry> baseline;
    std::string line;
    while (std::getline(in, line)) {
        auto p1 = line.find('|');
        auto p2 = line.find('|', p1+1);
        FileEntry f;
        f.hash = line.substr(0,p1);
        f.size = std::stoull(line.substr(p1+1,p2-p1-1));
        f.path = line.substr(p2+1);
        baseline[f.path] = f;
    }

    auto current = scan_directory(root);
    std::unordered_map<std::string, FileEntry> now;
    for (const auto& f : current) now[f.path] = f;

    std::vector<Event> events;

    for (const auto& [path,f] : now) {
        if (!baseline.count(path)) {
            std::string msg = "[+] NEW: " + path;
            std::cout << GREEN << msg << RESET << "\n";
            log_event(msg);
            events.push_back({path, "NEW", f.size, f.hash});
        }
        else if (baseline[path].hash != f.hash) {
            std::string msg = "[!] MODIFIED: " + path;
            std::cout << YELLOW << msg << RESET << "\n";
            log_event(msg);
            events.push_back({path, "MODIFIED", f.size, f.hash});
        }
    }

    for (const auto& [path,f] : baseline) {
        if (!now.count(path)) {
            std::string msg = "[-] DELETED: " + path;
            std::cout << RED << msg << RESET << "\n";
            log_event(msg);
            events.push_back({path, "DELETED", f.size, f.hash});
        }
    }

    if (!events.empty()) write_html_report(events);
}

// Monitor directory continuously
void monitor_directory(const std::string& root, unsigned int interval_seconds) {
    std::cout << "[+] Monitoring " << root << " every " << interval_seconds << " seconds. Ctrl+C to stop.\n";
    while (true) {
        scan_and_compare(root);
        std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
    }
}
