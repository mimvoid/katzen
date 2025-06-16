#pragma once
#include <raylib.h>
#include <cstdint>

namespace katzen {
enum class State { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Color border;
  Color base;
  Color text;
};

/**
 * A drawing context, which keeps track of simple theme variables for fewer
 * lookups, and stores a widget state that can be passed to children.
 */
struct Dctx {
  const uint8_t borderWidth;
  const uint8_t borderRadius;
  const uint8_t iconSize;

  StateColors colors;
  State state = State::NORMAL;
  int cursor = MOUSE_CURSOR_DEFAULT;
};
} // namespace katzen
