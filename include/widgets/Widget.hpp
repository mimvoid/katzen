#ifndef KATZE_WIDGETS_WIDGET_HPP
#define KATZE_WIDGETS_WIDGET_HPP

#include "../core/Rect.hpp"
#include "../core/Vec2.hpp"
#include "../ctx/Gctx.hpp"

namespace katze {
struct Dctx;

/**
 * Variable data for a widget.
 */
struct Widget {
  virtual ~Widget() = default;

  void reposition(FVec2 position, FRect &rect);
  virtual void resize(Gctx g, FRect &rect);
  virtual void view(Dctx &d, FRect rect) = 0;
};
} // namespace katze

#endif // !KATZE_WIDGETS_WIDGET_HPP
