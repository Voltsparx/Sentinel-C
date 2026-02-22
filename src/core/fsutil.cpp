#include "fsutil.h"
#include "config.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <system_error>

namespace fs = std::filesystem;

namespace fsutil {

void ensure_dirs() {
    std::error_code ec;
    fs::create_directories(config::DATA_DIR, ec);
    fs::create_directories(config::LOG_DIR, ec);
    fs::create_directories(config::REPORT_CLI_DIR, ec);
    fs::create_directories(config::REPORT_HTML_DIR, ec);
    fs::create_directories(config::REPORT_JSON_DIR, ec);
    fs::create_directories(config::REPORT_CSV_DIR, ec);
}

std::string timestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto t = std::chrono::system_clock::to_time_t(now);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now.time_since_epoch()) %
                    1000;
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y%m%d_%H%M%S")
       << "_" << std::setw(3) << std::setfill('0') << ms.count();
    return ss.str();
}

std::string sanitize_token(const std::string& value, const std::string& fallback) {
    if (value.empty()) {
        return fallback.empty() ? "scan" : fallback;
    }

    std::string out;
    out.reserve(value.size());

    for (const unsigned char ch : value) {
        if (std::isalnum(ch) != 0 || ch == '-' || ch == '_') {
            out.push_back(static_cast<char>(ch));
        } else {
            out.push_back('_');
        }
    }

    // Collapse repeated underscores for cleaner names.
    out.erase(std::unique(out.begin(), out.end(), [](char left, char right) {
                  return left == '_' && right == '_';
              }),
              out.end());

    while (!out.empty() && out.front() == '_') {
        out.erase(out.begin());
    }
    while (!out.empty() && out.back() == '_') {
        out.pop_back();
    }

    if (out.empty()) {
        return fallback.empty() ? "scan" : fallback;
    }
    return out;
}

} // namespace fsutil