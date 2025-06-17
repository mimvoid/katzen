#pragma once
#include <cstdint>
#include "Axis.hpp"

namespace katzen {
enum class Edge : uint8_t { TOP, RIGHT, BOTTOM, LEFT };

struct Edges {
  int top = 0;
  int right = 0;
  int bottom = 0;
  int left = 0;

  constexpr Edges(int top, int right, int bottom, int left)
      : top(top), right(right), bottom(bottom), left(left) {}

  constexpr Edges(int top, int x, int bottom)
      : top(top), right(x), bottom(bottom), left(x) {}

  constexpr Edges(int y, int x) : Edges(y, x, y, x) {}

  constexpr Edges(int val) : Edges(val, val) {}

  constexpr Edges() {}

  constexpr bool operator==(const Edges &other) const {
    return (top == other.top) && (right == other.right)
           && (bottom == other.bottom) && (left == other.left);
  }

  constexpr bool operator!=(const Edges &other) const {
    return (top != other.top) || (right != other.right)
           || (bottom != other.bottom) || (left != other.left);
  }

  constexpr int get(Edge edge) const {
    switch (edge) {
    case Edge::TOP:    return top;
    case Edge::RIGHT:  return right;
    case Edge::BOTTOM: return bottom;
    default:           return left;
    }
  }

  /**
   * Gets the sum of the values by axis.
   */
  constexpr int get(Axis axis) const {
    switch (axis) {
    case Axis::X: return left + right;
    case Axis::Y: return top + bottom;
    }
  }

  constexpr void set(Edge edge, int value) {
    switch (edge) {
    case Edge::TOP:    top = value; break;
    case Edge::RIGHT:  right = value; break;
    case Edge::BOTTOM: bottom = value; break;
    case Edge::LEFT:   left = value; break;
    }
  }

  /**
   * Assigns all edges to one value.
   *
   * @param value The value to assign
   */
  constexpr void set(int value) {
    top = value;
    right = value;
    bottom = value;
    left = value;
  }

  /**
   * Assigns all edge values by axis.
   *
   * @param y The value for the top and bottom
   * @param x The value for left and right
   */
  constexpr void set(int y, int x) {
    top = y;
    right = x;
    bottom = y;
    left = x;
  }

  /**
   * Assigns top, bottom, and horizontal values, CSS-style.
   *
   * @param top The value for the top
   * @param x The value for left and right
   * @param bottom The value for the bottom
   */
  constexpr void set(int top, int x, int bottom) {
    this->top = top;
    right = x;
    this->bottom = bottom;
    left = x;
  }
};
} // namespace katzen
