#pragma once

namespace katzen {
enum class Axis : bool { X, Y };

constexpr Axis flip(Axis axis) {
  switch (axis) {
  case Axis::X: return Axis::Y;
  case Axis::Y: return Axis::X;
  }
}
} // namespace katzen
