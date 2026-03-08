project(GameboyEmu)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXPORT_COMPILE_COMMANDS ON)

include_directories(inc)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(GameboyEmu ${SOURCES})
