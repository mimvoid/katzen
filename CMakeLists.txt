cmake_minimum_required(VERSION 3.25)

project(katzen
  LANGUAGES CXX
  VERSION 0.1.0
  HOMEPAGE_URL "https://github.com/mimvoid/katzen"
)

option(KATZEN_BUILD_INSTALL "Generate the install target for katzen" ON)
option(KATZEN_BUILD_TESTS "Build the tests for katzen" OFF)
option(KATZEN_BUILD_EXAMPLES "Build the examples for katzen" OFF)

add_subdirectory(include katzen)

if (KATZEN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (KATZEN_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
