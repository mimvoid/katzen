#pragma once
#include <raylib.h>
#include <cstdint>

namespace katzen {
struct Rgb {
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};

  constexpr bool operator==(const Rgb &that) const {
    return r == that.r && g == that.g && b == that.b;
  }
  constexpr bool operator!=(const Rgb &that) const { return !(*this == that); }

  explicit constexpr operator Color() const { return Color{r, g, b, 255}; }
};

struct Rgba : Rgb {
  uint8_t a{0};

  constexpr bool operator==(const Rgba &that) const {
    return r == that.r && g == that.g && b == that.b && a == that.a;
  }
  constexpr bool operator!=(const Rgba &that) const { return !(*this == that); }

  explicit constexpr operator Color() const { return Color{r, g, b, a}; }
};
} // namespace katzen
