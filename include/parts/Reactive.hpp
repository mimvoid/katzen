#pragma once
#include "../core/Dctx.hpp"
#include "../theme.hpp"

namespace katzen {
/**
 * A widget component that is sensitive to mouse hovering and clicks.
 * If disabled, it does not update its colors.
 */
struct Reactive {
  constexpr State state() const { return m_state; }
  constexpr bool enabled() const { return m_state != State::DISABLED; }

  constexpr void enable() {
    if (m_state == State::DISABLED) {
      m_state = State::NORMAL;
    }
  }

  constexpr void disable() { m_state = State::DISABLED; }
  constexpr void toggle() { m_state == State::DISABLED ? enable() : disable(); }

protected:
  State m_state{State::NORMAL};

  /**
   * Updates the state and colors based on whether the given area is focused or
   * pressed.
   *
   * @param widgetArea The mouse-sensitive area of the widget.
   * @returns Whether the widget area has been pressed.
   */
  bool updateState(Dctx &d, Rectangle widgetArea) {
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
};
} // namespace katzen
