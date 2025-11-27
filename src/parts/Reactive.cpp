#include "parts/Reactive.hpp"
#include "theme.hpp"

namespace katzen {
bool Reactive::updateState(Dctx &d, Rectangle widgetArea) {
  bool pressed = false;

  if (m_state != State::DISABLED) {
    if (CheckCollisionPointRec(GetMousePosition(), widgetArea)) {
      m_state =
          IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? State::ACTIVE : State::FOCUS;

      d.cursor = MOUSE_CURSOR_POINTING_HAND;
      pressed = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    } else {
      m_state = State::NORMAL;
    }
  }

  if (m_state != d.state) {
    // The state changed, update colors
    d.state = m_state;
    d.colors = theme::getStateColors(m_state);
  }

  return pressed;
}
}
