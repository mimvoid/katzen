cmake_minimum_required(VERSION 3.25)
project(katzen LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lc++abi")

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(tests)
