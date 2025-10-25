add_executable(katzen_tests
  core/test_align.cpp
  core/test_edges.cpp
  core/test_rect.cpp
  core/test_vectors.cpp
  widgets/test_widget.cpp
  widgets/test_icon.cpp
)

# Dependencies
find_package(Catch2 3 REQUIRED)
target_link_libraries(katzen_tests PRIVATE
  katzen
  Catch2::Catch2WithMain
)
