#pragma once
#include "../theming/themer.hpp"

namespace katzen {
/**
 * A widget component that is sensitive to mouse hovering and clicks.
 * If disabled, it does not update its colors.
 */
class Reactive {
public:
  constexpr State state() const { return m_state; }
  constexpr bool enabled() const { return m_state != State::DISABLED; }

  void enable() {
    if (m_state != State::DISABLED) return;

    m_state = State::NORMAL;
    m_colors = theme::getStateColors(State::NORMAL);
  }

  void disable() {
    if (m_state == State::DISABLED) return;

    m_state = State::DISABLED;
    m_colors = theme::getStateColors(State::DISABLED);
  }

  void toggle() { m_state == State::DISABLED ? enable() : disable(); }

protected:
  State m_state = State::NORMAL;
  theme::StateColors m_colors = theme::getStateColors(State::NORMAL);

  /**
   * Updates the state and colors based on whether the given area is focused or
   * pressed.
   *
   * @param widgetArea The mouse-sensitive area of the widget.
   * @returns Whether the widget area has been pressed.
   */
  bool updateState(Rectangle widgetArea) {
    bool pressed = false;

    if (m_state == State::DISABLED) {
      return pressed;
    }

    const State prevState = m_state;

    if (CheckCollisionPointRec(GetMousePosition(), widgetArea)) {
      m_state =
          IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? State::ACTIVE : State::FOCUS;

      pressed = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    } else {
      m_state = State::NORMAL;
    }

    if (m_state != prevState) {
      // The state changed, update colors
      m_colors = theme::getStateColors(m_state);
    }

    return pressed;
  }
};
} // namespace katzen
