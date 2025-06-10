#pragma once
#include <raylib.h>
#include "Axis.hpp"
#include "Edges.hpp"

namespace katzen {
template <typename T>
struct rect_t {
  T x, y, w, h;

  constexpr bool operator==(const rect_t &other) const {
    return (x == other.x) && (y == other.y) && (w == other.w) && (h == other.h);
  }
  constexpr bool operator!=(const rect_t &other) const {
    return (x != other.x) || (y != other.y) || (w != other.w) || (h != other.h);
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

typedef rect_t<float> Rect;

template <typename T>
constexpr Rectangle rlRectangle(rect_t<T> rec) {
  return {(float)rec.x, (float)rec.y, (float)rec.w, (float)rec.h};
}
} // namespace katzen
