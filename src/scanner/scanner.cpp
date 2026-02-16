#include "scanner.h"
#include "ignore.h"
#include "hash.h"
#include "../core/logger.h"
#include "../core/config.h"
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

namespace scanner {

static FileEntry read_entry(const fs::directory_entry& f) {
    FileEntry e;
    e.path  = f.path().string();
    e.size  = f.file_size();
    e.mtime = decltype(e.mtime)(
        fs::last_write_time(f).time_since_epoch().count()
    );
    e.hash  = hash::sha256_file(e.path);
    return e;
}

ScanResult run_scan(const std::string& target) {
    ScanResult result;
    ignore::load();

    FileMap baseline;
    bool baseline_ok = load_baseline(baseline);

    auto start = std::chrono::steady_clock::now();

    for (auto& p : fs::recursive_directory_iterator(target)) {
        if (!p.is_regular_file()) continue;

        std::string path = p.path().string();
        if (ignore::match(path)) continue;

        FileEntry entry = read_entry(p);
        result.current[path] = entry;
        result.stats.scanned++;

        if (!baseline_ok || baseline.find(path) == baseline.end()) {
            result.added[path] = entry;
            result.stats.added++;
            logger::success("[NEW] " + path);
        } else {
            const auto& old = baseline[path];
            if (old.hash != entry.hash || old.size != entry.size) {
                result.modified[path] = entry;
                result.stats.modified++;
                logger::warning("[MODIFIED] " + path);
            }
        }
    }

    if (baseline_ok) {
        for (const auto& [path, old] : baseline) {
            if (result.current.find(path) == result.current.end()) {
                result.deleted[path] = old;
                result.stats.deleted++;
                logger::error("[DELETED] " + path);
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    result.stats.duration =
        std::chrono::duration<double>(end - start).count();

    save_baseline(result.current);
    return result;
}

}
