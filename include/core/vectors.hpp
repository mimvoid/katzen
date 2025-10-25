#pragma once
#include <raylib.h>
#include "Axis.hpp"

namespace katzen {
template <typename T>
struct vec2_t {
  using value_type = T;

  T x = 0;
  T y = 0;

  // Explicit constructors

  constexpr vec2_t() noexcept {}
  constexpr vec2_t(T val) noexcept : x(val), y(val) {}
  constexpr vec2_t(T x, T y) noexcept : x(x), y(y) {}

  // Conversion constructors

  template <typename A, typename B>
  constexpr vec2_t(A x, B y) noexcept
      : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

  template <typename A>
  constexpr vec2_t(const vec2_t<A> &that) noexcept
      : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  constexpr vec2_t(const Vector2 &that) noexcept
      : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  // Operators

  constexpr operator Vector2() const {
    return {static_cast<float>(x), static_cast<float>(y)};
  }

  constexpr bool operator==(const vec2_t &that) const {
    return (x == that.x) && (y == that.y);
  }
  constexpr bool operator!=(const vec2_t &that) const {
    return !(*this == that);
  }
};

typedef vec2_t<float> Vec2;
typedef vec2_t<int> IVec2;
typedef vec2_t<unsigned int> UVec2;
typedef vec2_t<bool> BVec2;

/**************************/
/* Getting values by axis */
/**************************/

constexpr float get(Vector2 vec, Axis axis) {
  switch (axis) {
  case Axis::X: return vec.x;
  case Axis::Y: return vec.y;
  }
}

constexpr void set(Vector2 &vec, Axis axis, float value) {
  switch (axis) {
  case Axis::X: vec.x = value; break;
  case Axis::Y: vec.y = value; break;
  }
}

template <typename T>
constexpr T get(vec2_t<T> vec, Axis axis) {
  switch (axis) {
  case Axis::X: return vec.x;
  case Axis::Y: return vec.y;
  }
}

template <typename T>
constexpr void set(vec2_t<T> &vec, Axis axis, T value) {
  switch (axis) {
  case Axis::X: vec.x = value; break;
  case Axis::Y: vec.y = value; break;
  }
}
} // namespace katzen
