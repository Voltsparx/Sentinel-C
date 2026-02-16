#pragma once
#include "types.h"
#include <string>

namespace core {
    void print_summary(
        const std::string& target,
        const ScanStats& stats,
        const OutputPaths& paths,
        bool baseline_ok
    );
}
