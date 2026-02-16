#pragma once
#include <string>
#include <unordered_map>
#include "../core/types.h"

namespace scanner {

using FileMap = std::unordered_map<std::string, core::FileEntry>;

struct ScanResult {
    core::ScanStats stats;
    FileMap current;
    FileMap added;
    FileMap modified;
    FileMap deleted;
};

ScanResult run_scan(const std::string& target);
bool load_baseline(FileMap& baseline);
bool save_baseline(const FileMap& data);

}
