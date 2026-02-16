#include "scanner.h"
#include "../core/config.h"
#include <fstream>

namespace scanner {

bool load_baseline(FileMap& baseline) {
    baseline.clear();
    std::ifstream in(config::BASELINE_DB);
    if (!in.is_open()) return false;

    FileEntry e;
    while (in >> e.path >> e.hash >> e.size >> e.mtime) {
        baseline[e.path] = e;
    }
    return true;
}

bool save_baseline(const FileMap& data) {
    std::ofstream out(config::BASELINE_DB, std::ios::trunc);
    if (!out.is_open()) return false;

    for (const auto& [path, e] : data) {
        out << e.path << " "
            << e.hash << " "
            << e.size << " "
            << e.mtime << "\n";
    }
    return true;
}

}
