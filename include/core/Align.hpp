#pragma once
#include <cstdint>
#include "Axis.hpp"

namespace katzen {
enum class Align : uint8_t { START, CENTER, END };

struct AlignVec2 {
  Align x : 2;
  Align y : 2;

  constexpr AlignVec2() noexcept : x(Align::START), y(Align::START) {}
  constexpr AlignVec2(Align x, Align y) noexcept : x(x), y(y) {}

  constexpr Align get(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }
  constexpr void set(Axis axis, Align align) {
    switch (axis) {
    case Axis::X: x = align; break;
    case Axis::Y: y = align; break;
    }
  }
};

/**
 * Calculate how much to offset a child according to how it is aligned with the
 * parent.
 *
 * Any given size that is negative is considered 0.
 *
 * @param parentSize The size of the parent
 * @param childSize The size of the child
 * @param The alignment of the child in respect to the parent
 * @return How much the offset the child
 */
constexpr float offset(float parentSize, float childSize, Align align) {
  if (align == Align::START) {
    // There would be no offset needed regardless of size
    return 0.0f;
  }

  if (parentSize < 0.0f) parentSize = 0.0f;
  if (childSize < 0.0f) childSize = 0.0f;

  const float sizeDiff = parentSize - childSize;
  return (align == Align::CENTER) ? (sizeDiff / 2.0f) : sizeDiff;
}

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katzen] Test offset function") {
  SUBCASE("Start align offsets") {
    CHECK(offset(50.0f, 25.0f, Align::START) == 0.0f);
    CHECK(offset(50.0f, 50.0f, Align::START) == 0.0f);
    CHECK(offset(50.0f, 60.0f, Align::START) == 0.0f);
  }

  SUBCASE("Center align offsets") {
    CHECK(offset(60.0f, 20.0f, Align::CENTER) == 20.0f);
    CHECK(offset(50.0f, 50.0f, Align::CENTER) == 0.0f);
    CHECK(offset(40.0f, 60.0f, Align::CENTER) == -10.0f);
  }

  SUBCASE("End align offsets") {
    CHECK(offset(60.0f, 20.0f, Align::END) == 40.0f);
    CHECK(offset(50.0f, 50.0f, Align::END) == 0.0f);
    CHECK(offset(40.0f, 60.0f, Align::END) == -20.0f);
  }

  SUBCASE("Offset with negative sizes") {
    SUBCASE("Parent size is negative") {
      CHECK(offset(-10.0f, 20.0f, Align::START) == 0.0f);
      CHECK(offset(-10.0f, 20.0f, Align::CENTER) == -10.0f);
      CHECK(offset(-10.0f, 20.0f, Align::END) == -20.0f);
    }

    SUBCASE("Child size is negative") {
      CHECK(offset(20.0f, -10.0f, Align::START) == 0.0f);
      CHECK(offset(20.0f, -10.0f, Align::CENTER) == 10.0f);
      CHECK(offset(20.0f, -10.0f, Align::END) == 20.0f);
    }

    SUBCASE("Parent and child sizes are negative") {
      CHECK(offset(-20.0f, -10.0f, Align::START) == 0.0f);
      CHECK(offset(-20.0f, -10.0f, Align::CENTER) == 0.0f);
      CHECK(offset(-20.0f, -10.0f, Align::END) == 0.0f);
    }
  }
}
#endif
} // namespace katzen
