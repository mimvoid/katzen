#pragma once
#include "Axis.hpp"
#include "vectors.hpp"

namespace katzen {
struct Bounds {
  UVec2 min;
  UVec2 max;

  constexpr bool operator==(const Bounds &other) const {
    return (min == other.min) && (max == other.max);
  }

  constexpr bool operator!=(const Bounds &other) const {
    return (min != other.min) || (max != other.max);
  }

  // Set the minimum width, increasing the maximum width if needed.
  constexpr void minWidth(unsigned int w) {
    if (w > max.x) max.x = w;
    min.x = w;
  }

  // Set the minimum height, increasing the maximum height if needed.
  constexpr void minHeight(unsigned int h) {
    if (h > max.y) max.y = h;
    min.y = h;
  }

  /**
   * Set the minimum width and height, increasing the maximum width or height
   * if needed.
   */
  constexpr void setMin(unsigned int w, unsigned int h) {
    minWidth(w);
    minHeight(h);
  }

  // Set the minimum size by axis
  constexpr void setMin(Axis axis, unsigned int value) {
    switch (axis) {
    case Axis::X: minWidth(value); break;
    case Axis::Y: minHeight(value); break;
    }
  }

  // Set the maximum width, constricting the minimum width if needed.
  constexpr void maxWidth(unsigned int w) {
    if (w < min.x) min.x = w;
    max.x = w;
  }

  // Set the maximum height, constricting the minimum height if needed.
  constexpr void maxHeight(unsigned int h) {
    if (h < min.y) min.y = h;
    max.y = h;
  }

  /**
   * Set the maximum width and height, constricting the minimum width or height
   * if needed.
   */
  constexpr void setMax(unsigned int w, unsigned int h) {
    maxWidth(w);
    maxHeight(h);
  }

  // Set the maximum size by axis
  constexpr void setMax(Axis axis, unsigned int value) {
    switch (axis) {
    case Axis::X: maxWidth(value); break;
    case Axis::Y: maxHeight(value); break;
    }
  }
};
} // namespace katzen
