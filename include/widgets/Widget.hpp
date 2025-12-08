#ifndef KATZE_WIDGETS_WIDGET_HPP
#define KATZE_WIDGETS_WIDGET_HPP

#include "../core/Rect.hpp"
#include "../ctx/Gctx.hpp"

namespace katze {
struct Dctx;

/**
 * Base data for a widget.
 */
struct WidgetData {
  FRect rect{}; // Position and size, including padding.
  FEdges padding{};
};

/**
 * Variable data for a widget.
 */
struct Widget {
  virtual ~Widget() = default;

  virtual void resize(Gctx g, WidgetData &wData) {
    wData.rect.w = g.clampWidth(wData.padding.getX());
    wData.rect.h = g.clampHeight(wData.padding.getY());
  }

  virtual void view(Dctx &d, const WidgetData &wData) = 0;
};

/**
 * Basic widget with no content. May be useful for specific layouts.
 */
struct Spacer : Widget {
  void view(
    [[maybe_unused]] Dctx &d, [[maybe_unused]] const WidgetData &wData
  ) override {}
};
} // namespace katze

#endif // !KATZE_WIDGETS_WIDGET_HPP
