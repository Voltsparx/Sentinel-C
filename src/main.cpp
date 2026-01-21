#include "scanner.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Sentinel-C — File Integrity Monitor\nUsage:\n"
                  << "  sentinel-c init <path>\n"
                  << "  sentinel-c scan <path>\n"
                  << "  sentinel-c monitor <path> [interval_seconds]\n";
        return 0;
    }

    std::string cmd = argv[1];
    std::string path = (argc > 2) ? argv[2] : ".";

    if (cmd == "init") initialize_baseline(path);
    else if (cmd == "scan") scan_and_compare(path);
    else if (cmd == "monitor") {
        unsigned int interval = (argc > 3) ? std::stoi(argv[3]) : 5;
        monitor_directory(path, interval);
    }
    else std::cout << "Unknown command\n";

    return 0;
}
