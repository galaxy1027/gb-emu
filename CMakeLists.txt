cmake_minimum_required(VERSION 3.12)
project(GameboyEmu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(GameboyEmu ${SOURCES})
target_include_directories(GameboyEmu PRIVATE ${CMAKE_SOURCE_DIR}/inc)
