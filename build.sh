#!/bin/bash

cmake -S . -B build
cmake --build build

cp -r Src/Assets build/