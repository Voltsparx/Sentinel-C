cmake_minimum_required(VERSION 3.10)

# Detect the system and compiler
if(NOT CMAKE_CXX_COMPILER)
  if(MSVC OR MSVC_IDE)
    message(STATUS "MSVC compiler detected")
  elseif(CMAKE_GENERATOR MATCHES "Unix Makefiles")
    message(STATUS "Unix Makefiles generator")
  endif()
endif()

project(SentinelC VERSION 3.50 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
    "src/*/*.cpp"
)

# Include directories
include_directories("src")
include_directories("src/core")
include_directories("src/scanner")
include_directories("src/reports")
include_directories("src/logs")

# Set output directory for binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add executable
add_executable(sentinel-c ${SRC_FILES})

# Optional: enable warnings for better code quality
if(MSVC)
    target_compile_options(sentinel-c PRIVATE /W4 /permissive-)
else()
    target_compile_options(sentinel-c PRIVATE -Wall -Wextra -pedantic -Wshadow)
endif()

message(STATUS "Sentinel-C v${PROJECT_VERSION} build configured.")
message(STATUS "Binary output will be placed in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# ============================================================================
# BUILD INSTRUCTIONS FOR DIFFERENT PLATFORMS
# ============================================================================
# 
# WINDOWS (with Visual Studio installed):
#   mkdir build
#   cd build
#   cmake -G "Visual Studio 17 2022" ..
#   cmake --build . --config Release
#
# WINDOWS (with MinGW):
#   mkdir build
#   cd build
#   cmake -G "MinGW Makefiles" ..
#   cmake --build .
#
# LINUX/macOS:
#   mkdir build
#   cd build
#   cmake ..
#   cmake --build .
#
# REQUIREMENTS:
#   - CMake >= 3.10
#   - C++17 compatible compiler (MSVC, GCC, or Clang)
#   - On Windows: Visual Studio 2015+ OR MinGW installed
# ============================================================================
