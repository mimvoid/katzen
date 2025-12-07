#ifndef KATZE_CORE_AXIS_HPP
#define KATZE_CORE_AXIS_HPP

namespace katze {
// Axes in a 2D space.
enum class Axis : bool { X, Y };

// Flips between the x and y axes.
constexpr Axis flip(Axis axis) {
  switch (axis) {
  case Axis::X: return Axis::Y;
  case Axis::Y: return Axis::X;
  }
}

// Flips between the x and y axes.
constexpr Axis operator!(Axis axis) { return flip(axis); }
} // namespace katze

#endif // !KATZE_CORE_AXIS_HPP
