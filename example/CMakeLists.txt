add_executable(katzen_widget_factory main.cpp)

target_link_libraries(katzen_widget_factory PRIVATE katzen)
target_link_options(katzen_widget_factory PRIVATE "LINKER:-as-needed")
