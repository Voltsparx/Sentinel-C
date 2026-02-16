#include "logger.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <ctime>

static std::ofstream log_stream;

static std::string timestamp() {
    std::time_t t = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return buf;
}

static std::string color(logger::Level lvl) {
    if (!config::COLOR_OUTPUT) return "";
    switch (lvl) {
        case logger::Level::SUCCESS: return "\033[32m";
        case logger::Level::WARNING: return "\033[33m";
        case logger::Level::ERROR:   return "\033[31m";
        default:                     return "\033[36m";
    }
}

namespace logger {

void init() {
    log_stream.open(config::LOG_FILE, std::ios::app);
}

void write(Level level, const std::string& message) {
    std::string ts = timestamp();
    std::string clr = color(level);
    std::string reset = config::COLOR_OUTPUT ? "\033[0m" : "";

    std::cout << clr << message << reset << "\n";

    if (log_stream.is_open()) {
        log_stream << "[" << ts << "] " << message << "\n";
    }
}

void info(const std::string& m)    { write(Level::INFO, m); }
void success(const std::string& m) { write(Level::SUCCESS, m); }
void warning(const std::string& m) { write(Level::WARNING, m); }
void error(const std::string& m)   { write(Level::ERROR, m); }

}
