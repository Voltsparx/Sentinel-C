#pragma once
#include <string>

namespace config {

// Directories
inline const std::string BASE_DIR   = "./";
inline const std::string DATA_DIR   = "sentinel-c-logs/data/";
inline const std::string REPORT_DIR = "sentinel-c-logs/reports/";
inline const std::string LOG_FILE   = DATA_DIR + ".sentinel.log";

// Files
inline const std::string BASELINE_FILE = DATA_DIR + ".sentinel-baseline";
inline const std::string IGNORE_FILE   = "./.sentinelignore";

// Scan settings
inline const bool VERBOSE = true;

} // namespace config
