#include "banner.h"
#include "core/colors.h"
#include "core/config.h"
#include "core/metadata.h"
#include <iostream>
#include <string>

void show_banner() {
    const std::string logo =
        "   ____         __  _          __    _____\n"
        "  / __/__ ___  / /_(_)__  ___ / /___/ ___/\n"
        " _\\ \\/ -_) _ \\/ __/ / _ \\/ -_) /___/ /__  \n"
        "/___/\\__/_//_/\\__/_/_//_/\\__/_/    \\___/  ";

    const std::string divider = "--------------------------------------------------";

    std::cout
        << colors::paint(logo, colors::Tone::Cyan) << "\n"
        << colors::paint(divider, colors::Tone::Grey) << "\n"
        << colors::paint(config::TOOL_NAME + " " + config::VERSION, colors::Tone::Green)
        << "  |  "
        << colors::paint("Advanced Host Defense Multi-Tool", colors::Tone::Yellow) << "\n"
        << colors::paint("Codename:", colors::Tone::Grey) << " "
        << colors::paint(config::CODENAME, colors::Tone::Magenta) << "\n"
        << colors::paint("By:", colors::Tone::Grey) << " "
        << colors::paint(metadata::AUTHOR, colors::Tone::Orange)
        << "    |  "
        << colors::paint("Contact:", colors::Tone::Grey) << " "
        << colors::paint(metadata::CONTACT, colors::Tone::Grey) << "\n"
        << colors::paint(divider, colors::Tone::Grey) << "\n\n";
}