#pragma once
#include <cstdint>
#include "Axis.hpp"

namespace katzen {
/**
 * Vector-like bitfield with single bit boolean values.
 */
struct BVec2 {
  bool x : 1;
  bool y : 1;

  // Default constructor, sets both fields to false.
  constexpr BVec2() noexcept : BVec2(false) {}

  // Constructor that initializes both fields to a value.
  constexpr BVec2(bool value) noexcept : BVec2(value, value) {}

  constexpr BVec2(bool x, bool y) noexcept : x(x), y(y) {}

  constexpr bool operator==(const BVec2 &that) const {
    return (x == that.x) && (y == that.y);
  }
  constexpr bool operator!=(const BVec2 &that) const {
    return !(*this == that);
  }

  constexpr operator uint8_t() const { return (x << 1) | y; }

  // Get the value for an axis.
  constexpr bool get(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }

  // Set the value for an axis.
  constexpr void set(Axis axis, bool value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }
};

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katzen] BVec2 to uint8_t") {
  CHECK((uint8_t)BVec2{false, false} == 0);
  CHECK((uint8_t)BVec2{false, true} == 1);
  CHECK((uint8_t)BVec2{true, false} == 2);
  CHECK((uint8_t)BVec2{true, true} == 3);
}

TEST_CASE("[katzen] Get BVec2 value by axis") {
  const BVec2 v{true, false};

  CHECK(v.get(Axis::X) == true);
  CHECK(v.get(Axis::Y) == false);
}

TEST_CASE("[katzen] Set Vec2 value by axis") {
  SUBCASE("Set value by x-axis") {
    BVec2 v{false, false};
    v.set(Axis::X, true);

    CHECK(v.x == true);
    CHECK(v.y == false);
  }

  SUBCASE("Set value by y-axis") {
    BVec2 v{false, true};
    v.set(Axis::Y, false);

    CHECK(v.x == false);
    CHECK(v.y == false);
  }
}
#endif
}; // namespace katzen
