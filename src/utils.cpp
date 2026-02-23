#include "utils.h"
#include "core/colors.h"

#include <chrono>
#include <iostream>
#include <thread>

void print_error(const std::string& msg) {
    std::cout << colors::paint("[-] " + msg, colors::Tone::Error) << "\n";
}

void print_success(const std::string& msg) {
    std::cout << colors::paint("[+] " + msg, colors::Tone::Success) << "\n";
}

void print_warning(const std::string& msg) {
    std::cout << colors::paint("[!] " + msg, colors::Tone::Warning) << "\n";
}

void print_info(const std::string& msg) {
    std::cout << colors::paint("[*] " + msg, colors::Tone::Info) << "\n";
}

// Spinner animation for scanning
void spinner_animation(const std::string& msg, int duration_seconds) {
    const char spin_chars[] = {'|', '/', '-', '\\'};
    int i = 0;
    auto start = std::chrono::steady_clock::now();
    while (true) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= duration_seconds) {
            break;
        }
        std::cout << "\r" << msg << " " << spin_chars[i % 4] << std::flush;
        ++i;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << "\r" << msg << " [done]\n";
}