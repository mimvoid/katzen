#pragma once

namespace katzen {
// Axes in a 2D space.
enum class Axis : bool { X, Y };

// Flips between the x and y axes.
constexpr Axis flip(Axis axis) {
  switch (axis) {
  case Axis::X: return Axis::Y;
  case Axis::Y: return Axis::X;
  }
}
} // namespace katzen
