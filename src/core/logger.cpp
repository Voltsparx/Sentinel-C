#include "logger.h"
#include "colors.h"
#include "config.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace {

std::ofstream log_stream;
std::mutex log_mutex;

std::tm local_time(std::time_t t) {
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    return tm;
}

std::string timestamp() {
    const std::time_t t = std::time(nullptr);
    const std::tm tm = local_time(t);
    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

const char* level_label(logger::Level level) {
    switch (level) {
        case logger::Level::SUCCESS: return "SUCCESS";
        case logger::Level::WARNING: return "WARN";
        case logger::Level::ERROR: return "ERROR";
        default: return "INFO";
    }
}

colors::Tone level_tone(logger::Level level) {
    switch (level) {
        case logger::Level::SUCCESS: return colors::Tone::Success;
        case logger::Level::WARNING: return colors::Tone::Warning;
        case logger::Level::ERROR: return colors::Tone::Error;
        default: return colors::Tone::Info;
    }
}

} // namespace

namespace logger {

void init() {
    std::lock_guard<std::mutex> guard(log_mutex);
    colors::initialize();
    if (!log_stream.is_open()) {
        log_stream.open(config::LOG_FILE, std::ios::app);
    }
}

void reopen() {
    std::lock_guard<std::mutex> guard(log_mutex);
    colors::initialize();
    if (log_stream.is_open()) {
        log_stream.close();
    }
    log_stream.open(config::LOG_FILE, std::ios::app);
}

void write(Level level, const std::string& message) {
    std::lock_guard<std::mutex> guard(log_mutex);
    const std::string prefix =
        "[" + timestamp() + "] [" + level_label(level) + "] ";

    if (colors::enabled()) {
        std::cout << colors::paint(prefix + message, level_tone(level)) << "\n";
    } else {
        std::cout << prefix << message << "\n";
    }

    if (log_stream.is_open()) {
        log_stream << prefix << message << "\n";
    }
}

void info(const std::string& m)    { write(Level::INFO, m); }
void success(const std::string& m) { write(Level::SUCCESS, m); }
void warning(const std::string& m) { write(Level::WARNING, m); }
void error(const std::string& m)   { write(Level::ERROR, m); }

} // namespace logger