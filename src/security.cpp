#include "security.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace security {

bool baseline_integrity_ok() {
    return fs::exists("sentinel-c-logs/data/.sentinel-baseline") &&
           fs::file_size("sentinel-c-logs/data/.sentinel-baseline") > 0;
}

}
