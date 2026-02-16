#pragma once
#include <string>
#include <vector>

namespace ignore {

void load();
bool match(const std::string& path);

}
