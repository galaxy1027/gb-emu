cmake_minimum_required(VERSION 3.12)
project(GameboyEmu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(GameboyEmu ${SOURCES})
target_include_directories(GameboyEmu PRIVATE ${CMAKE_SOURCE_DIR}/inc ${SDL2_INCLUDE_DIRS})

target_link_libraries(GameboyEmu ${SDL2_LIBRARIES})
