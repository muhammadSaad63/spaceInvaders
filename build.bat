@echo off

cmake -S . -B build
cmake --build build

xcopy "Src\Assets" "build\Assets" /E /I /Y

echo Executable has been built in the build folder