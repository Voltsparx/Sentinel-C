#include "cli_report.h"
#include "../core/config.h"
#include "../core/fsutil.h"
#include <fstream>

namespace reports {

void write_cli(const scanner::ScanResult& r) {
    std::string file =
        config::REPORT_CLI_DIR + "/scan_" + fsutil::timestamp() + ".txt";

    std::ofstream out(file);
    out << "Sentinel-C v3.50 — CLI Scan Report\n";
    out << "=================================\n\n";

    out << "Scanned Files : " << r.stats.scanned << "\n";
    out << "New Files     : " << r.stats.added << "\n";
    out << "Modified      : " << r.stats.modified << "\n";
    out << "Deleted       : " << r.stats.deleted << "\n";
    out << "Duration      : " << r.stats.duration << " sec\n\n";

    if (!r.added.empty()) {
        out << "[NEW FILES]\n";
        for (auto& [p,_] : r.added) out << " + " << p << "\n";
        out << "\n";
    }

    if (!r.modified.empty()) {
        out << "[MODIFIED FILES]\n";
        for (auto& [p,_] : r.modified) out << " ! " << p << "\n";
        out << "\n";
    }

    if (!r.deleted.empty()) {
        out << "[DELETED FILES]\n";
        for (auto& [p,_] : r.deleted) out << " - " << p << "\n";
        out << "\n";
    }

    out << "Recommended Actions:\n";
    if (!r.deleted.empty())
        out << "- Investigate deleted files immediately.\n";
    if (!r.modified.empty())
        out << "- Verify modifications against expected updates.\n";
    if (!r.added.empty())
        out << "- Review newly introduced files.\n";
    if (r.added.empty() && r.modified.empty() && r.deleted.empty())
        out << "- No action required. System integrity intact.\n";

    out << "\nReport Location:\n" << file << "\n";
}

}
