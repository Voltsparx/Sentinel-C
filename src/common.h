#pragma once
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "core/colors.h"

namespace common {

enum class LogLevel { INFO, ALERT, ERROR, SUCCESS };

struct FileEntry {
    std::string path;
    std::string hash;
    uintmax_t size;
    std::time_t mtime;
};

inline std::string now_string() {
    std::time_t t = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return buf;
}

inline void log(const std::string& msg, LogLevel lvl = LogLevel::INFO) {
    const char* tag = "[*]";
    colors::Tone tone = colors::Tone::Info;

    switch (lvl) {
        case LogLevel::SUCCESS:
            tag = "[+]";
            tone = colors::Tone::Success;
            break;
        case LogLevel::ALERT:
            tag = "[!]";
            tone = colors::Tone::Warning;
            break;
        case LogLevel::ERROR:
            tag = "[-]";
            tone = colors::Tone::Error;
            break;
        default:
            break;
    }

    std::cout << colors::paint(std::string(tag) + " " + msg, tone) << "\n";
}

} // namespace common