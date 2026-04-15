# ─────────────────────────────────────────────────────────────────────────────
#  Minimum CMake version required to process this file.
#  3.11+ is needed for FetchContent support.
# ─────────────────────────────────────────────────────────────────────────────
cmake_minimum_required(VERSION 3.11)


# ─────────────────────────────────────────────────────────────────────────────
#  Project name. This sets the ${PROJECT_NAME} variable to "space-invaders".
# ─────────────────────────────────────────────────────────────────────────────
project(space-invaders)


# ─────────────────────────────────────────────────────────────────────────────
#  In-source build guard.
#  Prevents running `cmake .` in the root folder, which pollutes it with build
#  files. Forces the user to do `cmake -B build` instead.
# ─────────────────────────────────────────────────────────────────────────────
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are prohibited. Use: cmake -B build")
endif()


# ─────────────────────────────────────────────────────────────────────────────
#  C++ standard.
#  CMAKE_CXX_STANDARD          → which C++ version to use (17 = C++17)
#  CMAKE_CXX_STANDARD_REQUIRED → if the compiler doesn't support it, error out
# ─────────────────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ─────────────────────────────────────────────────────────────────────────────
#  FetchContent — CMake's built-in module for downloading dependencies at
#  configure time (when you run `cmake -B build`). No manual installs needed.
# ─────────────────────────────────────────────────────────────────────────────
include(FetchContent)


# ── Raylib ────────────────────────────────────────────────────────────────────
#  FetchContent_Declare  → registers WHERE to get the library (doesn't
#                          download yet)
#  URL                   → downloads a specific release tarball from GitHub
#                          (faster than cloning the full git history)
# ──────────────────────────────────────────────────────────────────────────────
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)


# ──────────────────────────────────────────────────────────────────────────────
#  FetchContent_MakeAvailable → actually downloads, unpacks, and builds raylib
#                               making it available as a CMake target
# ──────────────────────────────────────────────────────────────────────────────
FetchContent_MakeAvailable(raylib)


# ── SQLiteCpp ─────────────────────────────────────────────────────────────────
#  SQLiteCpp is a C++ wrapper around the raw SQLite C API.
#  GIT_TAG pins the exact version so builds stay reproducible.
# ──────────────────────────────────────────────────────────────────────────────
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.1
)


# ──────────────────────────────────────────────────────────────────────────────
#  SQLITECPP_RUN_CPPLINT    → disables cpplint style checker (we don't need
#                              SQLiteCpp's own lint running on our machine)
#  SQLITECPP_INTERNAL_SQLITE → tells SQLiteCpp to bundle its own copy of
#                              SQLite, so we don't need a system SQLite install
#  CACHE BOOL "" FORCE      → writes the value into CMake's cache and forces
#                              it to override any previous value
# ──────────────────────────────────────────────────────────────────────────────
set(SQLITECPP_RUN_CPPLINT    OFF CACHE BOOL "" FORCE)
set(SQLITECPP_INTERNAL_SQLITE ON  CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SQLiteCpp)


# ─────────────────────────────────────────────────────────────────────────────
#  Source files list.
#  Every .cpp file that needs to be compiled is listed here.
#  CMake compiles each one into a .o object file, then links them together.
#  Note: .hpp headers are NOT listed — they're pulled in automatically via
#  #include directives in the .cpp files.
# ─────────────────────────────────────────────────────────────────────────────
set(SOURCES
    src/main.cpp                                            # Entry point

    # 1_core — foundational systems used across the whole game
    src/code/1_core/backGround/backGround.cpp               # Background rendering
    src/code/1_core/dataBase/dataBase.cpp                   # SQLite DB access layer
    src/code/1_core/enums/enums.cpp                         # Shared enums / constants

    # 2_entities — game objects that move, collide, and interact
    src/code/2_entities/aliens/aliens.cpp                   # Alien grid logic
    src/code/2_entities/lasers/lasers.cpp                   # Laser projectiles
    src/code/2_entities/motherShip/motherShip.cpp           # Bonus mothership
    src/code/2_entities/spaceShip/spaceShip.cpp             # Player ship

    # 3_states — one file per screen/state in the state machine
    src/code/3_states/1_state/state.cpp                     # Abstract base state
    src/code/3_states/2_menu/menu.cpp                       # Main menu screen
    src/code/3_states/3_play/play.cpp                       # Play screen wrapper
    src/code/3_states/4_shop/shop.cpp                       # Shop screen
    src/code/3_states/5_leaderBoards/leaderBoards.cpp       # Leaderboard screen
    src/code/3_states/6_history/history.cpp                 # Match history screen
    src/code/3_states/7_settings/settings.cpp               # Settings screen
    src/code/3_states/8_playing/playing.cpp                 # Active gameplay state
    src/code/3_states/9_paused/paused.cpp                   # Pause screen
    src/code/3_states/10_gameOver/gameOver.cpp              # Game over screen
    src/code/3_states/11_closeGame/closeGame.cpp            # Exit / cleanup state

    # 4_game — top-level game loop and state manager
    src/code/4_game/game.cpp                                # Game class, main loop
)


# ─────────────────────────────────────────────────────────────────────────────
#  Executable target.
#  add_executable(name, files...) tells CMake to compile all SOURCES and link
#  them into a single binary called "spaceInvaders".
# ─────────────────────────────────────────────────────────────────────────────
add_executable(spaceInvaders ${SOURCES})


# ─────────────────────────────────────────────────────────────────────────────
#  Include directories.
#  Tells the compiler WHERE to look when it sees #include "someHeader.hpp".
#  Without this, you'd need full relative paths in every #include.
#  PRIVATE means these paths are only used when compiling spaceInvaders itself,
#  not exposed to other targets that might depend on it.
# ─────────────────────────────────────────────────────────────────────────────
target_include_directories(spaceInvaders PRIVATE
    ${CMAKE_SOURCE_DIR}/src                                 # lets you do #include "code/..."

    # 1_core
    ${CMAKE_SOURCE_DIR}/src/code/1_core/backGround
    ${CMAKE_SOURCE_DIR}/src/code/1_core/dataBase
    ${CMAKE_SOURCE_DIR}/src/code/1_core/enums

    # 2_entities
    ${CMAKE_SOURCE_DIR}/src/code/2_entities/aliens
    ${CMAKE_SOURCE_DIR}/src/code/2_entities/lasers
    ${CMAKE_SOURCE_DIR}/src/code/2_entities/motherShip
    ${CMAKE_SOURCE_DIR}/src/code/2_entities/spaceShip

    # 3_states
    ${CMAKE_SOURCE_DIR}/src/code/3_states/1_state
    ${CMAKE_SOURCE_DIR}/src/code/3_states/2_menu
    ${CMAKE_SOURCE_DIR}/src/code/3_states/3_play
    ${CMAKE_SOURCE_DIR}/src/code/3_states/4_shop
    ${CMAKE_SOURCE_DIR}/src/code/3_states/5_leaderBoards
    ${CMAKE_SOURCE_DIR}/src/code/3_states/6_history
    ${CMAKE_SOURCE_DIR}/src/code/3_states/7_settings
    ${CMAKE_SOURCE_DIR}/src/code/3_states/8_playing
    ${CMAKE_SOURCE_DIR}/src/code/3_states/9_paused
    ${CMAKE_SOURCE_DIR}/src/code/3_states/10_gameOver
    ${CMAKE_SOURCE_DIR}/src/code/3_states/11_closeGame

    # 4_game
    ${CMAKE_SOURCE_DIR}/src/code/4_game
)


# ─────────────────────────────────────────────────────────────────────────────
#  Linking.
#  target_link_libraries → connects compiled libraries to our executable.
#  PRIVATE               → these libs are only needed by spaceInvaders itself.
#
#  Windows needs two extra system libs:
#    winmm  → Windows Multimedia API (audio, timers) — required by raylib
#    gdi32  → Windows Graphics Device Interface    — required by raylib
#
#  WIN32_EXECUTABLE TRUE → hides the console window on Windows so only the
#                          game window appears (remove while debugging)
# ─────────────────────────────────────────────────────────────────────────────
if(WIN32)
    target_link_libraries(spaceInvaders PRIVATE raylib SQLiteCpp winmm gdi32)
    set_target_properties(spaceInvaders PROPERTIES WIN32_EXECUTABLE TRUE)
else()
    # Linux / macOS only need raylib and SQLiteCpp
    target_link_libraries(spaceInvaders PRIVATE raylib SQLiteCpp)
endif()


# ─────────────────────────────────────────────────────────────────────────────
#  Asset deployment.
#  After the binary is built, this command copies the entire src/assets/ folder
#  next to the executable so the game can find its fonts, graphics, sounds, etc.
#
#  $<TARGET_FILE_DIR:spaceInvaders> → resolves to wherever the .exe/.out lands
#  (e.g. build/ on Linux, build/Debug/ on Windows with MSVC)
#
#  This runs every build, but cmake -E copy_directory is a no-op when nothing
#  has changed, so it doesn't slow things down.
# ─────────────────────────────────────────────────────────────────────────────
add_custom_command(TARGET spaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"
        "$<TARGET_FILE_DIR:spaceInvaders>/assets"
    COMMENT "Deploying assets for the space invaders to hide behind"
)