#pragma once
#include <raylib.h>
#include <type_traits>
#include "Axis.hpp"
#include "Edges.hpp"

namespace katzen {
template <typename T>
struct rect_t {
  static_assert(std::is_arithmetic_v<T>,
                "A katzen rect_t must contain an arithmetic type.");
  using value_type = T;

  T x = 0;
  T y = 0;
  T w = 0;
  T h = 0;

  constexpr bool operator==(const rect_t &that) const {
    return (x == that.x) && (y == that.y) && (w == that.w) && (h == that.h);
  }
  constexpr bool operator!=(const rect_t &that) const {
    return !(*this == that);
  }

  // Convert to raylib Rectangle
  constexpr operator Rectangle() const {
    return {static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(w),
            static_cast<float>(h)};
  }

  constexpr T position(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }

  constexpr void position(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }

  constexpr T size(Axis axis) const {
    switch (axis) {
    case Axis::X: return w;
    case Axis::Y: return h;
    }
  }

  constexpr void size(Axis axis, T value) {
    switch (axis) {
    case Axis::X: w = value; break;
    case Axis::Y: h = value; break;
    }
  }

  constexpr void translateX(T dx) { x += dx; }
  constexpr void translateY(T dy) { y += dy; }

  constexpr void translate(T dx, T dy) {
    x += dx;
    y += dy;
  }
  constexpr void translate(Axis axis, T value) {
    position(axis, position(axis) + value);
  }

  constexpr void clip(T dw, T dh) {
    w -= dw;
    h -= dh;
  }
  constexpr void clip(Axis axis, T value) { size(axis, size(axis) - value); }

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

    w -= padding.get(Axis::X);
    h -= padding.get(Axis::Y);
  }

  constexpr void expand(Edges margin) {
    x -= margin.left;
    y -= margin.top;

    w += margin.get(Axis::X);
    h += margin.get(Axis::Y);
  }
};

template <>
constexpr rect_t<float>::operator Rectangle() const {
  return {x, y, w, h};
}

typedef rect_t<float> Rect;
} // namespace katzen
