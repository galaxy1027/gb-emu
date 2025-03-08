cmake_minimum_required(VERSION 3.10)
project(gb-emu)
include_directories(include)
file(GLOB SOURCE "src/*.cpp")
add_executable(gb-emu ${SOURCE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

