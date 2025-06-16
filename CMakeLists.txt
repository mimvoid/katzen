cmake_minimum_required(VERSION 3.25)
project(katzen LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lc++abi")

option(KATZEN_BUILD_TESTS "Build the tests for katzen" OFF)
option(KATZEN_BUILD_EXAMPLES "Build the examples for katzen" OFF)

add_subdirectory(src katzen)

if (KATZEN_BUILD_TESTS)
enable_testing()
add_subdirectory(tests)
endif()

if (KATZEN_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()
