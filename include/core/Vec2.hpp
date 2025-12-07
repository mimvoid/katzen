#ifndef KATZE_CORE_VEC2_HPP
#define KATZE_CORE_VEC2_HPP

#include "Axis.hpp"

namespace katze {
template <typename T>
struct Vec2 {
  using value_type = T;

  T x{0};
  T y{0};

  constexpr Vec2() : Vec2(0, 0) {}
  constexpr Vec2(T val) : Vec2(val, val) {}
  constexpr Vec2(T x, T y) : x(x), y(y) {}

  // Conversion constructors

  template <typename A, typename B>
  constexpr Vec2(A x, B y)
    : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

  template <typename A>
  constexpr Vec2(const Vec2<A> &that)
    : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  // Operators

  constexpr bool operator==(const Vec2 &that) const {
    return x == that.x && y == that.y;
  }
  constexpr bool operator!=(const Vec2 &that) const { return !(*this == that); }

  // Methods

  constexpr T get(Axis axis) const { return (axis == Axis::X) ? x : y; }

  constexpr void set(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }
};

typedef Vec2<float> FVec2;
typedef Vec2<int> IVec2;
typedef Vec2<unsigned int> UVec2;

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katze] Get FVec2 value by axis") {
  const FVec2 v{1.0f, 2.0f};

  CHECK(v.get(Axis::X) == 1.0f);
  CHECK(v.get(Axis::Y) == 2.0f);
}

TEST_CASE("[katze] Set FVec2 value by axis") {
  SUBCASE("Set value by x-axis") {
    FVec2 v{1.0f, 2.0f};
    v.set(Axis::X, 3.0f);

    CHECK(v.x == 3.0f);
    CHECK(v.y == 2.0f);
  }

  SUBCASE("Set value by y-axis") {
    FVec2 v{1.0f, 2.0f};
    v.set(Axis::Y, 3.0f);

    CHECK(v.x == 1.0f);
    CHECK(v.y == 3.0f);
  }
}
#endif
} // namespace katze

#endif // !KATZE_CORE_VEC2_HPP
