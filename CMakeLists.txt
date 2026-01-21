cmake_minimum_required(VERSION 3.10)
project(SentinelC)

set(CMAKE_CXX_STANDARD 17)

add_executable(sentinel-c
    src/main.cpp
    src/scanner.cpp
    src/hasher.cpp
)
