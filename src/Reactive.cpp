#include "Reactive.hpp"
#include <SDL3/SDL_log.h>
#include "ctx/Dctx.hpp"

namespace katze {
bool containsMouse(FRect area, Dctx::MouseInfo m) {
  return m.x >= area.x && m.y >= area.y && m.x <= (area.x + area.w)
         && m.y <= (area.y + area.h);
}

bool Reactive::updateState(Dctx &d, FRect area) {
  using B = ButtonState;

  if (!enabled) {
    d.state = State::DISABLED;
    return false;
  }

  if (!d.mouse.valid) {
    d.state = State::NORMAL;
    return false;
  }

  if (d.root.focused == this) {
    // Widget was focused.

    if (d.mouse.leftButton == B::RELEASED || d.mouse.leftButton == B::UP) {
      d.root.focused = nullptr;
      d.state = State::NORMAL;
      return m_sticky || containsMouse(area, d.mouse);
    }

    d.state = State::ACTIVE;
    d.cursor = Cursor::POINTER;
    return false;
  }

  if (!d.root.focused && containsMouse(area, d.mouse)) {
    // No widget has already been focused, and mouse falls in widget area.

    d.cursor = Cursor::POINTER;

    if (d.mouse.leftButton == B::PRESSED) {
      d.root.focused = this;
      d.state = State::ACTIVE;
    } else {
      d.state = State::FOCUS;
    }
  } else {
    d.state = State::NORMAL;
  }

  return false;
};
} // namespace katze
