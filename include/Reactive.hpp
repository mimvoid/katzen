#ifndef KATZE_REACTIVE_HPP
#define KATZE_REACTIVE_HPP

#include "core/Rect.hpp"

namespace katze {
struct Dctx;

struct Reactive {
  bool enabled : 1;

  Reactive(bool enabled = false, bool sticky = false)
    : enabled(enabled), m_sticky(sticky) {}

  // Whether the callback still triggers if the mouse has left the widget.
  constexpr bool sticky() const { return m_sticky; }

protected:
  /**
   * Updates the Root, state, and colors based on whether the given area is
   * focused or pressed.
   *
   * @param d The drawing context
   * @param area The mouse-sensitive area of the widget.
   * @returns Whether the widget has been released.
   */
  bool updateState(Dctx &d, FRect area);

private:
  bool m_sticky : 1;
};
} // namespace katze

#endif // !KATZE_REACTIVE_HPP
