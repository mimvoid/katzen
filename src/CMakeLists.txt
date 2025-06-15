set(KATZEN_SOURCES
    components/icons.cpp
    components/Text.cpp
    theming/fonts.cpp
    theming/themer.cpp
    widgets/helpers.cpp
    widgets/Box.cpp
    widgets/Label.cpp
    widgets/IconLabel.cpp
)

set(KATZEN_PUBLIC_HEADERS
    katzen.hpp
    core.hpp
    widgets.hpp
    core/Align.hpp
    core/Axis.hpp
    core/Bounds.hpp
    core/Edges.hpp
    core/Gctx.hpp
    core/Rect.hpp
    core/vec.hpp
    components/icons.hpp
    components/Text.hpp
    components/Reactive.hpp
    widgets/Root.hpp
    widgets/Widget.hpp
    widgets/Spacer.hpp
    widgets/Box.hpp
    widgets/Button.hpp
    widgets/Icon.hpp
    widgets/IconLabel.hpp
    widgets/Label.hpp
)

add_library(katzen ${KATZEN_SOURCES} ${KATZEN_PUBLIC_HEADERS})
set_target_properties(katzen PROPERTIES
    PUBLIC_HEADER "${KATZEN_PUBLIC_HEADERS}"
    VERSION "${PROJECT_VERSION}"
)

# Dependencies
find_package(raylib REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(katzen PRIVATE raylib glm::glm)
target_link_options(katzen PRIVATE "LINKER:-as-needed")
