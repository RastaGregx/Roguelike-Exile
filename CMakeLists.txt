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

# Source and header files
set(SOURCES
    src/roguelike_exile.cpp
    src/player/player.cpp
    src/player/movement.cpp
    src/enemy.cpp
)

set(HEADERS
    include/player/player.h
    include/player/movement.h
    include/enemy.h
)

# Add the executable
add_executable(Roguelike-Exile ${SOURCES})

# Include directories (Make sure to include the Raylib headers)
target_include_directories(Roguelike-Exile PRIVATE include ${raylib_INCLUDE_DIRS})
#include_directories(${CMAKE_SOURCE_DIR}/include)


# Link Raylib
target_link_libraries(Roguelike-Exile PRIVATE raylib)

# Set C++ standard
set_property(TARGET Roguelike-Exile PROPERTY CXX_STANDARD 17)
set_property(TARGET Roguelike-Exile PROPERTY CXX_STANDARD_REQUIRED ON)

# # Additional options for MinGW (optional but recommended)
# if (MINGW)
#     target_compile_options(Roguelike-Exile PRIVATE -Wall -Wextra -Wpedantic)
# endif()
