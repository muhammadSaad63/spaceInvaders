cmake_minimum_required(VERSION 3.16)
project(SpaceInvaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─────────────────────────────────────────────
#  Output directories
# ─────────────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ─────────────────────────────────────────────
#  Options
# ─────────────────────────────────────────────
option(USE_RAYGUI "Enable raygui (header-only)" OFF)

# ─────────────────────────────────────────────
#  Dependencies
# ─────────────────────────────────────────────

# raylib
find_package(raylib REQUIRED)

# SQLite3 (low-level C library — required by SQLiteCpp)
find_package(SQLite3 REQUIRED)

# SQLiteCpp — try system install first, fall back to FetchContent
find_package(SQLiteCpp QUIET)
if(NOT SQLiteCpp_FOUND)
    message(STATUS "SQLiteCpp not found via find_package — fetching from GitHub")
    include(FetchContent)
    FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG        3.3.1
    )
    set(SQLITECPP_RUN_CPPLINT    OFF CACHE BOOL "" FORCE)
    set(SQLITECPP_RUN_CPPCHECK   OFF CACHE BOOL "" FORCE)
    set(SQLITECPP_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(SQLITECPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SQLiteCpp)
endif()

# ─────────────────────────────────────────────
#  Source files
# ─────────────────────────────────────────────
set(SOURCES
    src/main.cpp

    # 1_core
    src/code/1_core/backGround/backGround.cpp
    src/code/1_core/dataBase/dataBase.cpp
    src/code/1_core/enums/enums.cpp

    # 2_entities
    src/code/2_entities/aliens/aliens.cpp
    src/code/2_entities/lasers/lasers.cpp
    src/code/2_entities/motherShip/motherShip.cpp
    src/code/2_entities/spaceShip/spaceShip.cpp

    # 3_states
    src/code/3_states/1_state/state.cpp
    src/code/3_states/2_menu/menu.cpp
    src/code/3_states/3_play/play.cpp
    src/code/3_states/4_shop/shop.cpp
    src/code/3_states/5_leaderBoards/leaderBoards.cpp
    src/code/3_states/6_history/history.cpp
    src/code/3_states/7_settings/settings.cpp
    src/code/3_states/8_playing/playing.cpp
    src/code/3_states/9_paused/paused.cpp
    src/code/3_states/10_gameOver/gameOver.cpp
    src/code/3_states/11_closeGame/closeGame.cpp

    # 4_game
    src/code/4_game/game.cpp
)

# ─────────────────────────────────────────────
#  Executable
# ─────────────────────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES})

# ─────────────────────────────────────────────
#  Include directories
# ─────────────────────────────────────────────
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src

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

# ─────────────────────────────────────────────
#  raygui (header-only — just needs an include path)
# ─────────────────────────────────────────────
if(USE_RAYGUI)
    # Assumes raygui.h lives at: external/raygui/src/raygui.h
    # Adjust if yours differs
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/external/raygui/src
    )
    target_compile_definitions(${PROJECT_NAME} PRIVATE RAYGUI_IMPLEMENTATION)
endif()

# ─────────────────────────────────────────────
#  Link libraries
# ─────────────────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    SQLiteCpp
    SQLite::SQLite3
)

# ─────────────────────────────────────────────
#  Copy assets next to the binary after build
# ─────────────────────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets (data, fonts, graphics, sounds) to bin/"
)

# ─────────────────────────────────────────────
#  Platform-specific flags
# ─────────────────────────────────────────────
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        m dl pthread
    )
endif()