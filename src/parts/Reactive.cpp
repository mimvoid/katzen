#include "parts/Reactive.hpp"
#include <raylib.h>

namespace katzen {
bool Reactive::updateState(Dctx &d, Rectangle area) {
  if (!enabled) {
    d.state = State::DISABLED;
    return false;
  }

  if (m_locked) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      m_locked = false;
      d.state = State::NORMAL;
      return m_sticky || CheckCollisionPointRec(GetMousePosition(), area);
    }

    d.state = State::ACTIVE;
    d.cursor = MOUSE_CURSOR_POINTING_HAND;
    return false;
  }

  if (CheckCollisionPointRec(GetMousePosition(), area)) {
    // Mouse pointer falls in widget area
    d.cursor = MOUSE_CURSOR_POINTING_HAND;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      m_locked = true;
      d.state = State::ACTIVE;
    } else {
      d.state = State::FOCUS;
    }
  } else {
    d.state = State::NORMAL;
  }

  return false;
}
} // namespace katzen
