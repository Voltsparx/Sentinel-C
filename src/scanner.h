#pragma once
#include <string>
#include <vector>
struct FileEntry { std::string path; uintmax_t size; std::string hash; };

void initialize_baseline(const std::string& root);
void scan_and_compare(const std::string& root);
void monitor_directory(const std::string& root, unsigned int interval_seconds);
