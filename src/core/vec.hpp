#pragma once
#include "Axis.hpp"
#include <glm/vec2.hpp>

namespace katzen {
template <typename T, glm::qualifier Q = glm::defaultp>
constexpr T get(const glm::vec<2, T, Q> &vector2, Axis axis) {
  switch (axis) {
    case Axis::X:
      return vector2.x;
    case Axis::Y:
      return vector2.y;
  }
}

template <typename T, glm::qualifier Q = glm::defaultp>
constexpr void set(glm::vec<2, T, Q> &vector2, Axis axis, T value) {
  switch (axis) {
    case Axis::X:
      vector2.x = value;
      break;
    case Axis::Y:
      vector2.y = value;
      break;
  }
}
} // namespace katzen
