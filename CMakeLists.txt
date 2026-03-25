cmake_minimum_required(VERSION 3.11)
project(space-invaders)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are prohibited. Please create a build directory and run cmake from there (e.g., cmake -B build)")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# Fetching Raylib
FetchContent_Declare(
    raylib 
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Fetching SQLiteCpp
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.1
)

# Disables internel linting (honestly, no idea what this doing but i trust it)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_INTERNAL_SQLITE ON CACHE BOOL "" FORCE) 
FetchContent_MakeAvailable(SQLiteCpp)


add_executable(spaceInvaders src/spaceInvaders.cpp)

if(WIN32)
    target_link_libraries(spaceInvaders PRIVATE raylib SQLiteCpp winmm gdi32)
    set_target_properties(spaceInvaders PROPERTIES WIN32_EXECUTABLE TRUE)
else()
    target_link_libraries(spaceInvaders PRIVATE raylib SQLiteCpp)
endif()


# This command copies the Assets folder to the same directory where the executable lives
add_custom_command(TARGET spaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Assets"
    "$<TARGET_FILE_DIR:spaceInvaders>/Assets"
    COMMENT "Deploying assets for the space invaders to hide behind"
)