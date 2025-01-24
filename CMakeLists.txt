cmake_minimum_required(VERSION 3.15)

# Project setup
project(Roguelike-Exile VERSION 0.1.0 LANGUAGES C CXX)

# Dependencies
include(FetchContent)

# Enable testing (optional, if tests are required)
# include(CTest)
# enable_testing()

# Add path to the custom FindRaylib.cmake module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Raylib version
set(RAYLIB_VERSION 5.5)

# Fetch Raylib using FetchContent
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Fetch nlohmann JSON library using FetchContent
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2  # You can adjust the version as needed
)
FetchContent_MakeAvailable(nlohmann_json)

# Source and header files
set(SOURCES
    src/roguelike_exile.cpp

    src/player/player.cpp
    src/player/movement.cpp
    src/player/attack.cpp

    src/enemies/enemy.cpp
    src/enemies/enemyManager.cpp
    src/enemies/tank.cpp

    src/objects/objectManager.cpp

    src/utils/collision.cpp
    src/utils/gameState.cpp
    src/utils/inputControl.cpp
    src/utils/drawingUI.cpp
)

set(HEADERS
    include/player/player.h
    include/player/movement.h
    include/player/attack.h

    include/enemies/enemy.h
    include/enemies/enemyManager.h
    include/enemies/tank.h

    include/objects/objectManager.h
    include/objects/object.h

    include/utils/collision.h
    include/utils/gameState.h
    include/utils/inputControl.h
    include/utils/drawingUI.h

    include/map.h
)

# Asset directory setup
set(ASSET_DIR "assets")
set(OUTPUT_ASSET_DIR "${CMAKE_BINARY_DIR}/assets_copy")

# Ensure the output directory exists and is a directory, not a file
if(EXISTS ${OUTPUT_ASSET_DIR} AND NOT IS_DIRECTORY ${OUTPUT_ASSET_DIR})
    message(FATAL_ERROR "The path ${OUTPUT_ASSET_DIR} exists as a file, not a directory!")
elseif(NOT EXISTS ${OUTPUT_ASSET_DIR})
    file(MAKE_DIRECTORY ${OUTPUT_ASSET_DIR})
endif()

# Copy assets to the build output directory (including subdirectories)
file(COPY ${ASSET_DIR} DESTINATION ${OUTPUT_ASSET_DIR})

# Add the executable
add_executable(Roguelike-Exile ${SOURCES})

# Include directories (Make sure to include the Raylib headers)
target_include_directories(Roguelike-Exile PRIVATE include ${raylib_INCLUDE_DIRS})

# Link Raylib
target_link_libraries(Roguelike-Exile PRIVATE raylib)

# Link nlohmann JSON library (if required, it's header-only)
target_link_libraries(Roguelike-Exile PRIVATE nlohmann_json::nlohmann_json)

# Set C++ standard
set_property(TARGET Roguelike-Exile PROPERTY CXX_STANDARD 17)
set_property(TARGET Roguelike-Exile PROPERTY CXX_STANDARD_REQUIRED ON)

# # Additional options for MinGW (optional but recommended)
# if (MINGW)
#     target_compile_options(Roguelike-Exile PRIVATE -Wall -Wextra -Wpedantic)
# endif()
