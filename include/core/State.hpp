#pragma once
#include <raylib.h>
#include <cstdint>

namespace katzen {
enum class State : uint8_t { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Color border{0, 0, 0, 255};
  Color base{0, 0, 0, 255};
  Color text{0, 0, 0, 255};
};
} // namespace katzen
