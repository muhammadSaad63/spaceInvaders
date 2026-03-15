cmake_minimum_required(VERSION 3.11)
project(space-invaders)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz)
FetchContent_MakeAvailable(raylib)

add_executable(spaceInvaders Src/spaceInvaders.cpp)

if(WIN32)
    target_link_libraries(spaceInvaders PRIVATE raylib winmm gdi32)
    set_target_properties(spaceInvaders PROPERTIES WIN32_EXECUTABLE TRUE)
else()
    target_link_libraries(spaceInvaders PRIVATE raylib)
endif()