# 1. Minimum CMake version and project info
cmake_minimum_required(VERSION 3.25...3.32)
project(BioinfoParser-CPP VERSION 1.0 LANGUAGES CXX)

# 2. C++ Standard Configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 3. Compilation Flags for clean code (Warnings as Errors/High level)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

# 4. List all source files (.cpp)
set(SOURCES
    src/main.cpp
    src/BioSequence.cpp
    src/FastaParser.cpp
    src/ReportGenerator.cpp
)

# 5. CREATE THE EXECUTABLE
# This MUST come before target_include_directories
add_executable(bio_parser ${SOURCES})

# 6. Specify header directories (.hpp) for the created target
target_include_directories(bio_parser PRIVATE include)

# 7. Confirmation message during configuration
message(STATUS "Project ${PROJECT_NAME} configured for C++23.")