#include "colors.h"

#include <cstdlib>
#include <mutex>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

std::once_flag g_init_once;
bool g_enabled = true;

bool env_set(const char* key) {
    const char* value = std::getenv(key);
    return value != nullptr && value[0] != '\0';
}

bool detect_color_support() {
    if (env_set("NO_COLOR")) {
        return false;
    }

    if (const char* clicolor = std::getenv("CLICOLOR");
        clicolor != nullptr && clicolor[0] == '0' && clicolor[1] == '\0') {
        return false;
    }

    if (env_set("CLICOLOR_FORCE")) {
        return true;
    }

    if (const char* term = std::getenv("TERM");
        term != nullptr && std::string(term) == "dumb") {
        return false;
    }

    return true;
}

#ifdef _WIN32
bool enable_virtual_terminal() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD mode = 0;
    if (GetConsoleMode(handle, &mode) == 0) {
        return false;
    }

    if ((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0) {
        return true;
    }

    return SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}
#endif

void init_once() {
    g_enabled = detect_color_support();
#ifdef _WIN32
    if (g_enabled) {
        // On Windows terminals that do not support VT, avoid printing raw escape codes.
        g_enabled = enable_virtual_terminal();
    }
#endif
}

} // namespace

namespace colors {

void initialize() {
    std::call_once(g_init_once, init_once);
}

bool enabled() {
    initialize();
    return g_enabled;
}

const char* code(Tone tone) {
    switch (tone) {
        case Tone::Reset: return "\033[0m";
        case Tone::Success:
        case Tone::Green: return "\033[32m";
        case Tone::Warning:
        case Tone::Yellow: return "\033[33m";
        case Tone::Error:
        case Tone::Red: return "\033[31m";
        case Tone::Info:
        case Tone::Cyan: return "\033[36m";
        case Tone::Grey: return "\033[90m";
        case Tone::Magenta: return "\033[35m";
        case Tone::Orange: return "\033[38;5;208m";
        case Tone::Default: return "\033[39m";
    }
    return "\033[0m";
}

std::string paint(const std::string& text, Tone tone) {
    if (!enabled()) {
        return text;
    }
    return std::string(code(tone)) + text + code(Tone::Reset);
}

const char* clear_screen_sequence() {
    return "\033[2J\033[H";
}

} // namespace colors