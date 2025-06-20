add_library(katzen)

set(KATZEN_SOURCES
    components/icons.cpp
    components/textHelpers.cpp
    components/Text.cpp
    theme/fonts.cpp
    theme/themer.cpp
    widgets/Widget.cpp
    widgets/Box.cpp
    widgets/Checkbox.cpp
    widgets/Label.cpp
    widgets/IconLabel.cpp
    widgets/Slider.cpp
)

set(KATZEN_HEADERS
    katzen.hpp
    core.hpp
    widgets.hpp
    Root.hpp
    core/Align.hpp
    core/Axis.hpp
    core/Bounds.hpp
    core/Dctx.hpp
    core/Edges.hpp
    core/Gctx.hpp
    core/Rect.hpp
    core/vectors.hpp
    components/Container.hpp
    components/icons.hpp
    components/Text.hpp
    components/Reactive.hpp
    components/scales.hpp
    theme/fonts.hpp
    theme/FontStyle.hpp
    theme/Theme.hpp
    theme/themer.hpp
    widgets/Widget.hpp
    widgets/Spacer.hpp
    widgets/Box.hpp
    widgets/Button.hpp
    widgets/Checkbox.hpp
    widgets/Icon.hpp
    widgets/IconLabel.hpp
    widgets/Label.hpp
    widgets/Slider.hpp
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
