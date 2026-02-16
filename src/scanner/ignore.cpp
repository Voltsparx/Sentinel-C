#include "ignore.h"
#include "../core/config.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

static std::vector<std::string> rules;

namespace ignore {

void load() {
    rules.clear();
    std::ifstream in(config::IGNORE_FILE);
    if (!in.is_open()) return;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        rules.push_back(line);
    }
}

bool match(const std::string& path) {
    for (const auto& rule : rules) {
        if (path.find(rule) != std::string::npos)
            return true;
    }
    return false;
}

}
