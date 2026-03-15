@echo off

cmake -S . -B build
cmake --build build

xcopy "Src\Assets" "build\Assets" /E /I /Y