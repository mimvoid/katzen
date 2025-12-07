#ifndef KATZE_CORE_RECT_HPP
#define KATZE_CORE_RECT_HPP

#include <type_traits>
#include "Axis.hpp"
#include "Edges.hpp"

namespace katze {
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct Rect {
  using value_type = T;

  T x{0};
  T y{0};
  T w{0}; // width
  T h{0}; // height

  constexpr bool operator==(const Rect &that) const {
    return (x == that.x) && (y == that.y) && (w == that.w) && (h == that.h);
  }
  constexpr bool operator!=(const Rect &that) const { return !(*this == that); }

  // Get the position coordinate of the given axis.
  constexpr T position(Axis axis) const { return (axis == Axis::X) ? x : y; }

  // Set the position coordinate of the given axis.
  constexpr void setPosition(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }

  // Get the size (width or height) according to the given axis.
  constexpr T size(Axis axis) const { return (axis == Axis::X) ? w : h; }

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
    switch (axis) {
    case Axis::X: x += value; break;
    case Axis::Y: y += value; break;
    }
  }

  // Shrink the width and height.
  constexpr void clip(T dw, T dh) {
    w -= dw;
    h -= dh;
  }

  // Shrink a size by axis.
  constexpr void clip(Axis axis, T value) {
    switch (axis) {
    case Axis::X: w -= value; break;
    case Axis::Y: h -= value; break;
    }
  }

  constexpr void translateClip(T dx, T dy) {
    translate(dx, dy);
    clip(dx, dy);
  }
  constexpr void translateClip(Axis axis, T value) {
    switch (axis) {
    case Axis::X:
      x += value;
      w -= value;
      break;
    case Axis::Y:
      y += value;
      h -= value;
      break;
    }
  }

  constexpr void shrink(Edges<T> padding) {
    x += padding.left;
    y += padding.top;
    w -= padding.getX();
    h -= padding.getY();
  }

  constexpr void expand(Edges<T> margin) {
    x -= margin.left;
    y -= margin.top;
    w += margin.getX();
    h += margin.getY();
  }
};

typedef Rect<int> IRect;
typedef Rect<float> FRect;

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katze] Test FRect") {
  SUBCASE("Equality operators") {
    SUBCASE("FRects are equal") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect r2{1.0f, 2.0f, 40.0f, 90.0f};

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }

    SUBCASE("FRects are not equal") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect r2{2.0f, 2.0f, 40.0f, 80.0f};

      REQUIRE(r1 != r2);
      REQUIRE(!(r1 == r2));
    }

    SUBCASE("FRects are aliases") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect &r2 = r1;

      REQUIRE(r1 == r1);
      REQUIRE(!(r1 != r1));

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }
  }

  SUBCASE("Get FRect position by axis") {
    const FRect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.position(katze::Axis::X) == 1.0f);
    CHECK(rect.position(katze::Axis::Y) == 2.0f);
  }

  SUBCASE("Set FRect position by axis") {
    SUBCASE("Set position by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katze::Axis::X, 10.0f);
      CHECK(rect == FRect{10.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Set position by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katze::Axis::Y, 10.0f);
      CHECK(rect == FRect{1.0f, 10.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Get FRect size by axis") {
    const FRect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.size(katze::Axis::X) == 40.0f);
    CHECK(rect.size(katze::Axis::Y) == 90.0f);
  }

  SUBCASE("Set FRect size by axis") {
    SUBCASE("Set size by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katze::Axis::X, 10.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 10.0f, 90.0f});
    }

    SUBCASE("Set size by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katze::Axis::Y, 10.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 40.0f, 10.0f});
    }
  }

  SUBCASE("Translate x and y") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translate(5.0f, 5.0f);
    CHECK(rect == FRect{6.0f, 7.0f, 40.0f, 90.0f});
  }

  SUBCASE("Translate by axis") {
    SUBCASE("Translate by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{6.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Translate by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, -3.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Clip width and height") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.clip(10.0f, -20.0f);
    CHECK(rect == FRect{1.0f, 2.0f, 30.0f, 110.0f});
  }

  SUBCASE("Clip by axis") {
    SUBCASE("Clip by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Clip by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Translate clip") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translateClip(10.0f, -20.0f);
    CHECK(rect == FRect{11.0f, -18.0f, 30.0f, 110.0f});
  }

  SUBCASE("Translate clip by axis") {
    SUBCASE("Translate clip by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{6.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Translate clip by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, -3.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Pad FRect") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katze::Edges padding{1, 2, 5, 1};
    rect.pad(padding);
    CHECK(rect == FRect{2.0f, 3.0f, 37.0f, 84.0f});
  }

  SUBCASE("Expand FRect") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katze::Edges margin{1, 2, 5, 1};
    rect.expand(margin);
    CHECK(rect == FRect{0.0f, 1.0f, 43.0f, 96.0f});
  }
}
#endif
} // namespace katze

#endif // !KATZE_CORE_RECT_HPP
