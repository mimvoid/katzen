#ifndef KATZE_CORE_RGBA_HPP
#define KATZE_CORE_RGBA_HPP

#include <cstdint>

namespace katze {
struct Rgb {
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};

  constexpr bool operator==(const Rgb &that) const {
    return r == that.r && g == that.g && b == that.b;
  }
  constexpr bool operator!=(const Rgb &that) const { return !(*this == that); }
};

struct Rgba : Rgb {
  uint8_t a{255};

  constexpr bool operator==(const Rgba &that) const {
    return r == that.r && g == that.g && b == that.b && a == that.a;
  }
  constexpr bool operator!=(const Rgba &that) const { return !(*this == that); }
};
} // namespace katze

#endif // !KATZE_CORE_RGBA_HPP
