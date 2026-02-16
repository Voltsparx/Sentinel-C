#pragma once
#include <string>

namespace hasher {
    std::string sha256_file(const std::string& filepath);
} // namespace hasher
