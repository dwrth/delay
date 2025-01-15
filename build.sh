#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Generate build files with compile_commands.json
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Create symlink to compile_commands.json in root directory
ln -sf build/compile_commands.json .

# Build the project
cmake --build build