cmake_minimum_required(VERSION 3.14)

project(game-a
    VERSION 0.1
    DESCRIPTION "First pass of a game engine"
    LANGUAGES CXX C
)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" 
    CACHE STRING "Modules for CMake" 
    FORCE
)

add_subdirectory(third-party)

add_subdirectory(modules)