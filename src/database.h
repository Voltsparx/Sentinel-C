#pragma once
#include "common.h"
#include <vector>
#include <unordered_map>

namespace database {

void init_storage();
void save_baseline(const std::vector<common::FileEntry>& files);
std::unordered_map<std::string, common::FileEntry> load_baseline();

void log_action(const std::string& action, const std::string& path);

void generate_reports(
    const std::vector<common::FileEntry>& added,
    const std::vector<common::FileEntry>& modified,
    const std::vector<common::FileEntry>& deleted,
    const std::string& root
);

}
