#include "scanner.h"
#include "hasher.h"
#include "database.h"
#include "security.h"
#include "common.h"
#include <filesystem>

namespace fs = std::filesystem;

static std::vector<common::FileEntry> scan(const std::string& root) {
    std::vector<common::FileEntry> files;
    for (auto& e : fs::recursive_directory_iterator(root)) {
        if (!e.is_regular_file()) continue;

        common::FileEntry f;
        f.path = e.path().string();
        f.size = e.file_size();
        f.hash = hasher::sha256_file(f.path);
        files.push_back(f);
    }
    return files;
}

void initialize_baseline(const std::string& root) {
    database::init_storage();
    auto files = scan(root);
    database::save_baseline(files);
    common::log("Baseline initialized (" + std::to_string(files.size()) + " files)", common::LogLevel::SUCCESS);
}

void scan_and_compare(const std::string& root) {
    if (!security::baseline_integrity_ok()) {
        common::log("No baseline found. Run --init first.", common::LogLevel::ERROR);
        return;
    }

    auto base = database::load_baseline();
    auto cur  = scan(root);

    std::vector<common::FileEntry> A, M, D;

    for (auto& f : cur) {
        if (!base.count(f.path)) {
            A.push_back(f);
            common::log("NEW " + f.path, common::LogLevel::SUCCESS);
        } else if (base[f.path].hash != f.hash) {
            M.push_back(f);
            common::log("MODIFIED " + f.path, common::LogLevel::ALERT);
        }
    }

    for (auto& [p, f] : base) {
        bool found = false;
        for (auto& c : cur) if (c.path == p) found = true;
        if (!found) {
            D.push_back(f);
            common::log("DELETED " + p, common::LogLevel::ERROR);
        }
    }

    database::generate_reports(A, M, D, root);
}
