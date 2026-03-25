#!/bin/bash

cmake -S . -B build
cmake --build build

cp -r Src/Assets build/

echo "Executable has been built in the build folder"