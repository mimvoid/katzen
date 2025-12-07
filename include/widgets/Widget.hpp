#ifndef KATZE_WIDGETS_WIDGET_HPP
#define KATZE_WIDGETS_WIDGET_HPP

#include "../core/Edges.hpp"
#include "../core/Rect.hpp"

namespace katze {
struct Widget {
  IEdges padding{};

  // The position and size of the widget, regardless of other factors like
  // expansion in a container widget. Note that this includes padding.
  FRect m_rect{};
};
} // namespace katze

#endif // !KATZE_WIDGETS_WIDGET_HPP
