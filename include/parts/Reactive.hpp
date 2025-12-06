#pragma once
#include "../root/Dctx.hpp"

namespace katzen {
/**
 * A widget component that is sensitive to mouse hovering and clicks.
 * If disabled, it does not check for interactions or trigger any callback.
 */
struct Reactive {
  bool enabled : 1;

  Reactive() : enabled(true), m_locked(false), m_sticky(false) {}
  Reactive(bool sticky) : enabled(true), m_locked(false), m_sticky(sticky) {}

  // Whether the widget has been pressed on and not yet released.
  constexpr bool locked() const { return m_locked; }

protected:
  bool m_locked : 1;

  // Whether the callback still triggers if the mouse has left the widget.
  bool m_sticky : 1;

  /**
   * Updates the state and colors based on whether the given area is focused or
   * pressed.
   *
   * @param d The drawing context
   * @param widgetArea The mouse-sensitive area of the widget.
   * @returns Whether the widget area has been pressed.
   */
  bool updateState(Dctx &d, Rectangle area);
};
} // namespace katzen
