add_library(katzen)

set(KATZEN_SOURCES
  parts/icons.cpp
  parts/Text.cpp
  parts/textHelpers.cpp
  theme/fonts.cpp
  widgets/Box.cpp
  widgets/Checkbox.cpp
  widgets/Label.cpp
  widgets/Slider.cpp
  widgets/Widget.cpp
)
list(TRANSFORM KATZEN_SOURCES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(KATZEN_HEADERS
  katzen.hpp
  core.hpp
  widgets.hpp
  core/Align.hpp
  core/Axis.hpp
  core/Dctx.hpp
  core/DynamicCastPtr.hpp
  core/Edges.hpp
  core/Gctx.hpp
  core/Rect.hpp
  core/State.hpp
  core/vectors.hpp
  icons/katz_fill.h
  icons/katz_icons.hpp
  icons/katz_line.h
  parts/Container.hpp
  parts/icons.hpp
  parts/Reactive.hpp
  parts/scales.hpp
  parts/Text.hpp
  parts/textHelpers.hpp
  widgets/Box.hpp
  widgets/Button.hpp
  widgets/Checkbox.hpp
  widgets/Icon.hpp
  widgets/Label.hpp
  widgets/Slider.hpp
  widgets/Spacer.hpp
  widgets/Widget.hpp
  widgets/WidgetBuilder.hpp
)

target_sources(katzen PRIVATE ${KATZEN_SOURCES})
target_sources(katzen PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  FILES ${KATZEN_HEADERS}
)

set_target_properties(katzen PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(katzen PUBLIC cxx_std_17)

# Dependencies
find_package(raylib REQUIRED)
target_link_libraries(katzen PRIVATE raylib)

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
  install(
    FILES "${CMAKE_SOURCE_DIR}/icons/katz_icons.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/katzen"
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
