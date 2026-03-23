#!/bin/bash

# 1. Build the project using CMake's universal command
# Using -p to ensure it doesn't fail if the directory exists
mkdir -p build && cd build

# Configure and Build
cmake .. 
cmake --build . --config Debug

# 2. Logic to detect the binary path (Cross-platform)
# MSVC (Windows) creates a Debug folder, Unix/macOS puts it in the root of build/
if [ -f "./Debug/bio_parser.exe" ]; then
    BINARY="./Debug/bio_parser.exe"
elif [ -f "./bio_parser" ]; then
    BINARY="./bio_parser"
else
    echo "CRITICAL ERROR: Binary not found. Check build logs."
    exit 1
fi

echo "Using binary at: $BINARY"

# 3. Run with a corrupted file to test error handling
echo "---------------------------------------"
echo "Testing error handling (Bad Data)..."
if [ -f "../data/bad_data.fasta" ]; then
    $BINARY --input ../data/bad_data.fasta --output error_test
else
    echo "WARNING: ../data/bad_data.fasta not found. Skipping error test."
fi
echo "---------------------------------------"

# 4. Run with real data
echo "Testing real data analysis..."
if [ -f "../data/test.fasta" ]; then
    $BINARY --input ../data/test.fasta --output final_result
else
    echo "ERROR: ../data/test.fasta not found in 'data' folder. Skip real data test."
fi

echo "---------------------------------------"
echo "Tests finished. Check the 'build' folder for output files."