#!/bin/bash

mkdir -p XCodeBuild
cmake -B XCodeBuild -G Xcode

mkdir -p build
cmake -B build
cmake --build build
