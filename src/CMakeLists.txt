set(KATZEN_SOURCES
    components/icons.cpp
    components/textHelpers.cpp
    theme/fonts.cpp
    theme/themer.cpp
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
    core/Align.hpp
    core/Axis.hpp
    core/Bounds.hpp
    core/Dctx.hpp
    core/Edges.hpp
    core/Gctx.hpp
    core/Rect.hpp
    components/Container.hpp
    components/icons.hpp
    components/Text.hpp
    components/Reactive.hpp
    components/scales.hpp
    theme/themer.hpp
    theme/fonts.hpp
    theme/Theme.hpp
    theme/ThemeFont.hpp
    widgets/Root.hpp
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

add_library(katzen ${KATZEN_SOURCES})
target_sources(katzen PUBLIC
    FILE_SET HEADERS
    TYPE HEADERS
    FILES ${KATZEN_HEADERS}
)

set_target_properties(katzen PROPERTIES VERSION ${PROJECT_VERSION})

# Dependencies
find_package(raylib REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(katzen PRIVATE raylib glm::glm)
target_link_options(katzen PRIVATE "LINKER:-as-needed")

# Installation
install(TARGETS katzen
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    EXPORT katzenTargets
    FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/katzen"
)

install(FILES "${CMAKE_SOURCE_DIR}/icons/katz_icons.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/katzen"
)
