#pragma once
#include "core/State.hpp"
#include "theme/FontStyle.hpp"
#include "theme/Theme.hpp"

namespace katzen {
/**
 * A drawing context that provides theme settings and stores a widget state
 * that can be passed to children.
 */
struct Dctx {
  const Theme &theme;
  FontStyle font{};
  State state{State::NORMAL};
  uint8_t cursor{MOUSE_CURSOR_DEFAULT};

  constexpr const StateColors &colors() const {
    return theme.stateColors(state);
  }
};
} // namespace katzen
