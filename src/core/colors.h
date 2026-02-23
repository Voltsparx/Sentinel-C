#pragma once

#include <string>

namespace colors {

enum class Tone {
    Reset,
    Default,
    Success,
    Warning,
    Error,
    Info,
    Cyan,
    Green,
    Yellow,
    Red,
    Grey,
    Magenta,
    Orange
};

void initialize();
bool enabled();
const char* code(Tone tone);
std::string paint(const std::string& text, Tone tone);
const char* clear_screen_sequence();

} // namespace colors