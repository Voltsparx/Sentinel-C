#pragma once
#include <string>

void print_error(const std::string& msg);
void print_success(const std::string& msg);
void print_warning(const std::string& msg);
void print_info(const std::string& msg);
void spinner_animation(const std::string& msg, int duration_seconds);
