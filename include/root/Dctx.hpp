#pragma once
#include "core/State.hpp"
#include "theme/FontStyle.hpp"

namespace katzen {
/**
 * A drawing context, which keeps track of simple theme variables for fewer
 * lookups, and stores a widget state that can be passed to children.
 */
struct Dctx {
  FontStyle font{};
  StateColors colors{};

  const uint8_t borderWidth{2};
  const uint8_t borderRadius{0};
  const uint8_t iconSize{1};

  State state{State::NORMAL};
  uint8_t cursor{MOUSE_CURSOR_DEFAULT};
};
} // namespace katzen
