#pragma once
#include <string>

namespace config {

// Tool info
inline const std::string TOOL_NAME    = "Sentinel-C";
inline const std::string VERSION      = "v3.50";
inline const std::string CODENAME     = "AEGIS";

// Base directories
inline const std::string ROOT_DIR     = "sentinel-c-logs";
inline const std::string DATA_DIR     = ROOT_DIR + "/data";
inline const std::string LOG_DIR      = ROOT_DIR + "/logs";
inline const std::string REPORT_DIR   = ROOT_DIR + "/reports";

// Report subdirectories
inline const std::string REPORT_CLI   = REPORT_DIR + "/cli";
inline const std::string REPORT_HTML  = REPORT_DIR + "/html";
inline const std::string REPORT_JSON  = REPORT_DIR + "/json";

// Files
inline const std::string BASELINE_DB  = DATA_DIR + "/baseline.db";
inline const std::string LOG_FILE     = LOG_DIR  + "/sentinel.log";
inline const std::string IGNORE_FILE  = ".sentinelignore";

// Behavior
inline const bool COLOR_OUTPUT        = true;
inline const bool VERBOSE             = true;

} // namespace config
