#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

void print_error(const std::string& msg) {
    std::cout << "\033[31m[-] " << msg << "\033[0m\n";
}

void print_success(const std::string& msg) {
    std::cout << "\033[32m[+] " << msg << "\033[0m\n";
}

void print_warning(const std::string& msg) {
    std::cout << "\033[33m[!] " << msg << "\033[0m\n";
}

void print_info(const std::string& msg) {
    std::cout << "\033[36m[*] " << msg << "\033[0m\n";
}

// Spinner animation for scanning
void spinner_animation(const std::string& msg, int duration_seconds) {
    const char spin_chars[] = {'|', '/', '-', '\\'};
    int i = 0;
    auto start = std::chrono::steady_clock::now();
    while (true) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= duration_seconds)
            break;
        std::cout << "\r" << msg << " " << spin_chars[i % 4] << std::flush;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << "\r" << msg << " ✔\n";
}
