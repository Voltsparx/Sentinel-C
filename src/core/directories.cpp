#include "directories.h"
#include "config.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace core {

void ensure_directories() {
    fs::create_directories(config::DATA_DIR);
    fs::create_directories(config::LOG_DIR);
    fs::create_directories(config::REPORT_CLI);
    fs::create_directories(config::REPORT_HTML);
    fs::create_directories(config::REPORT_JSON);
}

}
