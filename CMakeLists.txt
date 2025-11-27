cmake_minimum_required(VERSION 3.25)

project(katzen
  LANGUAGES CXX
  VERSION 0.1.0
  DESCRIPTION "GUI library written in C++17"
  HOMEPAGE_URL "https://github.com/mimvoid/katzen"
)

option(KATZEN_BUILD_INSTALL "Generate the install target for katzen" ON)
option(KATZEN_BUILD_TESTS "Build the tests for katzen" OFF)
option(KATZEN_BUILD_EXAMPLES "Build the examples for katzen" OFF)

# Library configuration

add_library(katzen)

target_compile_features(katzen PRIVATE cxx_std_17)
target_compile_options(katzen PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(katzen PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Dependencies
find_package(raylib REQUIRED)
target_link_libraries(katzen PRIVATE raylib)

# Sources
add_subdirectory(src)

# Headers
add_subdirectory(include)

if (KATZEN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (KATZEN_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Installation
if (KATZEN_BUILD_INSTALL)
  include(GNUInstallDirs)

  install(TARGETS katzen
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    EXPORT katzenTargets
    FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/katzen"
  )
  install(EXPORT katzenTargets
    NAMESPACE katzen::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/katzen"
  )

  include(CMakePackageConfigHelpers)

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/katzenConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
  )
  install(FILES
    "${CMAKE_SOURCE_DIR}/cmake/katzenConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/katzenConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/katzen"
  )
endif()
