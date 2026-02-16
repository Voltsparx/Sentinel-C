#include "scanner.h"
#include <iostream>

namespace cli {

void parse(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Sentinel-C v3.50\n"
                  << "--init <path>\n"
                  << "--scan <path>\n";
        return;
    }

    std::string cmd = argv[1];
    std::string path = argv[2];

    if (cmd == "--init") initialize_baseline(path);
    else if (cmd == "--scan") scan_and_compare(path);
}

} // namespace cli
