# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.26)
project(brainfucked C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SOURCES src/*.cpp src/*/*.cpp)
add_executable(brainfucked ${SOURCES})

target_precompile_headers(brainfucked
  PUBLIC src/brainfucked.hpp 
  PRIVATE <iostream> <vector>
)