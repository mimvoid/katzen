#include <catch2/catch_test_macros.hpp>
#include "../../src/core/vectors.hpp"

using katzen::Axis;
using katzen::Vec2;

TEST_CASE("Get vec2 value by axis") {
  const Vec2 v{1.0f, 2.0f};

  SECTION("Get value by x-axis") { REQUIRE(katzen::get(v, Axis::X) == 1.0f); }
  SECTION("Get value by y-axis") { REQUIRE(katzen::get(v, Axis::Y) == 2.0f); }
}

TEST_CASE("Set vec2 value by axis") {
  SECTION("Set value by x-axis") {
    Vec2 v{1.0f, 2.0f};
    katzen::set(v, Axis::X, 3.0f);

    REQUIRE(v.x == 3.0f);
    REQUIRE(v.y == 2.0f);
  }

  SECTION("Set value by y-axis") {
    Vec2 v{1.0f, 2.0f};
    katzen::set(v, Axis::Y, 3.0f);

    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 3.0f);
  }
}
