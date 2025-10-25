#pragma once
#include <raylib.h>
#include <cstdint>

namespace katzen {
enum class State : uint8_t { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Color border;
  Color base;
  Color text;
};
} // namespace katzen
