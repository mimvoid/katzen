add_executable(katzen_widget_factory main.cpp)

if (NOT TARGET katzen)
    find_package(katzen REQUIRED)
endif()

target_link_libraries(katzen_widget_factory PRIVATE katzen)
