#pragma once
#include "State.hpp"

namespace katzen {
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
  uint8_t cursor = MOUSE_CURSOR_DEFAULT;
};
} // namespace katzen
