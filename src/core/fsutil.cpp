#include "fsutil.h"
#include "config.h"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

namespace fsutil {

void ensure_dirs() {
    fs::create_directories(config::BIN_DIR);
    fs::create_directories(config::DATA_DIR);
    fs::create_directories(config::LOG_DIR);
    fs::create_directories(config::REPORT_CLI_DIR);
    fs::create_directories(config::REPORT_HTML_DIR);
    fs::create_directories(config::REPORT_JSON_DIR);
}

std::string timestamp() {
    auto now = std::chrono::system_clock::now();
    auto t   = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return ss.str();
}

}
