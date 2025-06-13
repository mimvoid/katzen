#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif

#include <catch2/catch_test_macros.hpp>
#include "../../src/widgets/Label.hpp"
#include <raylib.h>

using katzen::widgets::Label;

TEST_CASE("Initial fields", "[label]") {
  const Label label0(GetFontDefault(), "Dummy label");
  REQUIRE(TextIsEqual(label0.text.data(), "Dummy label"));

  const Label label1(GetFontDefault(), "Another", 32.0f);
  REQUIRE(TextIsEqual(label1.text.data(), "Another"));
}
