#pragma once
#include <raylib.h>
#include "Axis.hpp"

namespace katzen {
template <typename T>
struct vec2_t {
  using value_type = T;

  T x{0};
  T y{0};

  // Explicit constructors

  constexpr explicit vec2_t() noexcept {}
  constexpr explicit vec2_t(T val) noexcept : x(val), y(val) {}
  constexpr explicit vec2_t(T x, T y) noexcept : x(x), y(y) {}

  // Conversion constructors

  template <typename A, typename B>
  constexpr vec2_t(A x, B y) noexcept
      : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

  template <typename A>
  constexpr vec2_t(const vec2_t<A> &that) noexcept
      : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  constexpr explicit vec2_t(const Vector2 &that) noexcept
      : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  // Operators

  constexpr explicit operator Vector2() const {
    return {static_cast<float>(x), static_cast<float>(y)};
  }

  constexpr bool operator==(const vec2_t &that) const {
    return (x == that.x) && (y == that.y);
  }
  constexpr bool operator!=(const vec2_t &that) const {
    return !(*this == that);
  }

  // Methods

  constexpr T get(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }

  constexpr void set(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }
};

typedef vec2_t<float> Vec2;
typedef vec2_t<int> IVec2;
typedef vec2_t<unsigned int> UVec2;

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katzen] Get Vec2 value by axis") {
  const Vec2 v{1.0f, 2.0f};

  CHECK(v.get(Axis::X) == 1.0f);
  CHECK(v.get(Axis::Y) == 2.0f);
}

TEST_CASE("[katzen] Set Vec2 value by axis") {
  SUBCASE("Set value by x-axis") {
    Vec2 v{1.0f, 2.0f};
    v.set(Axis::X, 3.0f);

    CHECK(v.x == 3.0f);
    CHECK(v.y == 2.0f);
  }

  SUBCASE("Set value by y-axis") {
    Vec2 v{1.0f, 2.0f};
    v.set(Axis::Y, 3.0f);

    CHECK(v.x == 1.0f);
    CHECK(v.y == 3.0f);
  }
}
#endif
} // namespace katzen
