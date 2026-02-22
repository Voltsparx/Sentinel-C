#include "json_report.h"
#include "advice.h"
#include "../core/config.h"
#include "../core/fsutil.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::string escape_json(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (char c : text) {
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\b': out += "\\b"; break;
            case '\f': out += "\\f"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default: out += c; break;
        }
    }
    return out;
}

std::string format_mtime(std::time_t timestamp) {
    if (timestamp <= 0) {
        return "-";
    }

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &timestamp);
#else
    localtime_r(&timestamp, &tm);
#endif

    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

std::vector<const core::FileEntry*> sorted_entries(const scanner::FileMap& data) {
    std::vector<const core::FileEntry*> entries;
    entries.reserve(data.size());
    for (const auto& item : data) {
        entries.push_back(&item.second);
    }
    std::sort(entries.begin(), entries.end(), [](const core::FileEntry* left, const core::FileEntry* right) {
        return left->path < right->path;
    });
    return entries;
}

void write_entries(std::ofstream& out,
                   const char* name,
                   const scanner::FileMap& data,
                   bool trailing_comma) {
    const auto entries = sorted_entries(data);

    out << "  \"" << name << "\": [\n";
    for (std::size_t index = 0; index < entries.size(); ++index) {
        const core::FileEntry& entry = *entries[index];
        out << "    {"
            << "\"path\":\"" << escape_json(entry.path) << "\"," 
            << "\"size\":" << entry.size << ","
            << "\"mtime\":" << entry.mtime << ","
            << "\"mtime_text\":\"" << escape_json(format_mtime(entry.mtime)) << "\"," 
            << "\"sha256\":\"" << escape_json(entry.hash) << "\""
            << "}";
        if (index + 1 < entries.size()) {
            out << ",";
        }
        out << "\n";
    }
    out << "  ]";
    if (trailing_comma) {
        out << ",";
    }
    out << "\n";
}

void write_string_array(std::ofstream& out,
                        const char* key,
                        const std::vector<std::string>& values,
                        bool trailing_comma) {
    out << "    \"" << key << "\": [\n";
    for (std::size_t i = 0; i < values.size(); ++i) {
        out << "      \"" << escape_json(values[i]) << "\"";
        if (i + 1 < values.size()) {
            out << ",";
        }
        out << "\n";
    }
    out << "    ]";
    if (trailing_comma) {
        out << ",";
    }
    out << "\n";
}

} // namespace

namespace reports {

std::string write_json(const scanner::ScanResult& result, const std::string& scan_id) {
    const std::string raw_id = scan_id.empty() ? fsutil::timestamp() : scan_id;
    const std::string id = fsutil::sanitize_token(raw_id, "scan");
    const std::string file =
        config::REPORT_JSON_DIR + "/sentinel-c_integrity_json_report_" + id + ".json";

    std::ofstream out(file, std::ios::trunc);
    if (!out.is_open()) {
        return "";
    }

    const AdvisorNarrative narrative = advisor_narrative(result);
    const std::string status = advisor_status(result);

    out << "{\n";
    out << "  \"version\": \"" << escape_json(config::VERSION) << "\",\n";
    out << "  \"scan_id\": \"" << escape_json(id) << "\",\n";
    out << "  \"generated_at\": \"" << escape_json(format_mtime(std::time(nullptr))) << "\",\n";
    out << "  \"status\": \"" << status << "\",\n";
    out << "  \"stats\": {\n";
    out << "    \"scanned\": " << result.stats.scanned << ",\n";
    out << "    \"added\": " << result.stats.added << ",\n";
    out << "    \"modified\": " << result.stats.modified << ",\n";
    out << "    \"deleted\": " << result.stats.deleted << ",\n";
    out << "    \"duration\": " << result.stats.duration << "\n";
    out << "  },\n";
    write_entries(out, "new", result.added, true);
    write_entries(out, "modified", result.modified, true);
    write_entries(out, "deleted", result.deleted, true);
    out << "  \"advisor\": {\n";
    out << "    \"summary\": \"" << escape_json(narrative.summary) << "\",\n";
    out << "    \"risk_level\": \"" << escape_json(narrative.risk_level) << "\",\n";
    write_string_array(out, "whys", narrative.whys, true);
    write_string_array(out, "what_matters", narrative.what_matters, true);
    write_string_array(out, "teaching", narrative.teaching, true);
    write_string_array(out, "next_steps", narrative.next_steps, false);
    out << "  }\n";
    out << "}\n";

    return file;
}

} // namespace reports