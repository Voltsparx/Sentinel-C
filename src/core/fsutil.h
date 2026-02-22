#pragma once
#include <string>

namespace fsutil {
    void ensure_dirs();
    std::string timestamp();
    std::string sanitize_token(const std::string& value,
                               const std::string& fallback = "scan");
}