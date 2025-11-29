#pragma once
#include "Rgba.hpp"
#include <cstdint>

namespace katzen {
enum class State : uint8_t { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Rgb border{};
  Rgb base{};
  Rgb text{};
};
} // namespace katzen
