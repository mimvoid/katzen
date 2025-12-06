#pragma once
#include <raylib.h>
#include <type_traits>
#include "Axis.hpp"
#include "Edges.hpp"

namespace katzen {
template <typename T>
struct rect_t {
  static_assert(
    std::is_arithmetic_v<T>, "A katzen rect_t must contain an arithmetic type."
  );

  using value_type = T;

  T x{0};
  T y{0};
  T w{0}; // width
  T h{0}; // height

  constexpr bool operator==(const rect_t &that) const {
    return (x == that.x) && (y == that.y) && (w == that.w) && (h == that.h);
  }
  constexpr bool operator!=(const rect_t &that) const {
    return !(*this == that);
  }

  // Convert to raylib Rectangle.
  constexpr explicit operator Rectangle() const {
    return {
      static_cast<float>(x),
      static_cast<float>(y),
      static_cast<float>(w),
      static_cast<float>(h)
    };
  }

  // Get the position coordinate of the given axis.
  constexpr T position(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }

  // Set the position coordinate of the given axis.
  constexpr void setPosition(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }

  // Get the size (width or height) according to the given axis.
  constexpr T size(Axis axis) const {
    switch (axis) {
    case Axis::X: return w;
    case Axis::Y: return h;
    }
  }

  // Set the size (width or height) according to the given axis.
  constexpr void setSize(Axis axis, T value) {
    switch (axis) {
    case Axis::X: w = value; break;
    case Axis::Y: h = value; break;
    }
  }

  /**
   * Set the sizes of both axes.
   *
   * @param axis The given axis.
   * @param axisValue Value to set for the given axis.
   * @param antiAxisValue Value to set for the opposite of the given axis.
   */
  constexpr void setSizes(Axis axis, T axisValue, T antiAxisValue) {
    switch (axis) {
    case Axis::X:
      w = axisValue;
      h = antiAxisValue;
      break;
    case Axis::Y:
      w = antiAxisValue;
      h = axisValue;
      break;
    }
  }

  // Add to the x-axis.
  constexpr void translateX(T dx) { x += dx; }

  // Add to the y-axis.
  constexpr void translateY(T dy) { y += dy; }

  // Add to the position coordinates.
  constexpr void translate(T dx, T dy) {
    x += dx;
    y += dy;
  }

  // Add to a position coordinate by axis.
  constexpr void translate(Axis axis, T value) {
    setPosition(axis, position(axis) + value);
  }

  // Shrink the width and height.
  constexpr void clip(T dw, T dh) {
    w -= dw;
    h -= dh;
  }

  // Shrink a size by axis.
  constexpr void clip(Axis axis, T value) { setSize(axis, size(axis) - value); }

  constexpr void translateClip(T dx, T dy) {
    translate(dx, dy);
    clip(dx, dy);
  }
  constexpr void translateClip(Axis axis, T value) {
    translate(axis, value);
    clip(axis, value);
  }

  constexpr void pad(Edges padding) {
    x += padding.left;
    y += padding.top;

    w -= padding.getSum(Axis::X);
    h -= padding.getSum(Axis::Y);
  }

  constexpr void expand(Edges margin) {
    x -= margin.left;
    y -= margin.top;

    w += margin.getSum(Axis::X);
    h += margin.getSum(Axis::Y);
  }
};

template <>
constexpr rect_t<float>::operator Rectangle() const {
  return {x, y, w, h};
}

typedef rect_t<float> Rect;

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katzen] Test Rect") {
  SUBCASE("Equality operators") {
    SUBCASE("Rects are equal") {
      const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const Rect r2{1.0f, 2.0f, 40.0f, 90.0f};

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }

    SUBCASE("Rects are not equal") {
      const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const Rect r2{2.0f, 2.0f, 40.0f, 80.0f};

      REQUIRE(r1 != r2);
      REQUIRE(!(r1 == r2));
    }

    SUBCASE("Rects are aliases") {
      const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const Rect &r2 = r1;

      REQUIRE(r1 == r1);
      REQUIRE(!(r1 != r1));

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }
  }

  SUBCASE("Get Rect position by axis") {
    const Rect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.position(katzen::Axis::X) == 1.0f);
    CHECK(rect.position(katzen::Axis::Y) == 2.0f);
  }

  SUBCASE("Set Rect position by axis") {
    SUBCASE("Set position by x-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katzen::Axis::X, 10.0f);
      CHECK(rect == Rect{10.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Set position by y-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katzen::Axis::Y, 10.0f);
      CHECK(rect == Rect{1.0f, 10.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Get Rect size by axis") {
    const Rect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.size(katzen::Axis::X) == 40.0f);
    CHECK(rect.size(katzen::Axis::Y) == 90.0f);
  }

  SUBCASE("Set Rect size by axis") {
    SUBCASE("Set size by x-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katzen::Axis::X, 10.0f);
      CHECK(rect == Rect{1.0f, 2.0f, 10.0f, 90.0f});
    }

    SUBCASE("Set size by y-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katzen::Axis::Y, 10.0f);
      CHECK(rect == Rect{1.0f, 2.0f, 40.0f, 10.0f});
    }
  }

  SUBCASE("Translate x and y") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translate(5.0f, 5.0f);
    CHECK(rect == Rect{6.0f, 7.0f, 40.0f, 90.0f});
  }

  SUBCASE("Translate by axis") {
    SUBCASE("Translate by x-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katzen::Axis::X, 5.0f);
      CHECK(rect == Rect{6.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Translate by y-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katzen::Axis::Y, -5.0f);
      CHECK(rect == Rect{1.0f, -3.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Clip width and height") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.clip(10.0f, -20.0f);
    CHECK(rect == Rect{1.0f, 2.0f, 30.0f, 110.0f});
  }

  SUBCASE("Clip by axis") {
    SUBCASE("Clip by x-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katzen::Axis::X, 5.0f);
      CHECK(rect == Rect{1.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Clip by y-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katzen::Axis::Y, -5.0f);
      CHECK(rect == Rect{1.0f, 2.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Translate clip") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translateClip(10.0f, -20.0f);
    CHECK(rect == Rect{11.0f, -18.0f, 30.0f, 110.0f});
  }

  SUBCASE("Translate clip by axis") {
    SUBCASE("Translate clip by x-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katzen::Axis::X, 5.0f);
      CHECK(rect == Rect{6.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Translate clip by y-axis") {
      Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katzen::Axis::Y, -5.0f);
      CHECK(rect == Rect{1.0f, -3.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Pad Rect") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katzen::Edges padding{1, 2, 5, 1};
    rect.pad(padding);
    CHECK(rect == Rect{2.0f, 3.0f, 37.0f, 84.0f});
  }

  SUBCASE("Expand Rect") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katzen::Edges margin{1, 2, 5, 1};
    rect.expand(margin);
    CHECK(rect == Rect{0.0f, 1.0f, 43.0f, 96.0f});
  }
}
#endif
} // namespace katzen
