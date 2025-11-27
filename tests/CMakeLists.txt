enable_testing()

add_executable(katzen_tests
  doctest.cpp
  widgets/testIcon.cpp
  widgets/testWidget.cpp
)

target_compile_features(katzen_tests PRIVATE cxx_std_17)
target_include_directories(katzen_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(doctest REQUIRED)
target_link_libraries(katzen_tests PRIVATE doctest::doctest katzen)

add_test(NAME katzen_tests COMMAND katzen_tests)
