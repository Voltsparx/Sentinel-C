#include "json_report.h"
#include "../core/config.h"
#include "../core/fsutil.h"
#include <fstream>

namespace reports {

void write_json(const scanner::ScanResult& r) {
    std::string file =
        config::REPORT_JSON_DIR + "/scan_" + fsutil::timestamp() + ".json";

    std::ofstream out(file);
    out << "{\n";
    out << "  \"version\": \"3.50\",\n";
    out << "  \"stats\": {\n";
    out << "    \"scanned\": " << r.stats.scanned << ",\n";
    out << "    \"added\": " << r.stats.added << ",\n";
    out << "    \"modified\": " << r.stats.modified << ",\n";
    out << "    \"deleted\": " << r.stats.deleted << "\n";
    out << "  }\n";
    out << "}\n";
}

}
