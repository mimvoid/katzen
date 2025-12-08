#ifndef KATZE_WIDGETS_RECTANGLE_HPP
#define KATZE_WIDGETS_RECTANGLE_HPP

#include "Widget.hpp"

namespace katze {
/**
 * Simple rectangle widget.
 */
struct Rectangle : Widget {
  void view(Dctx &d, const WidgetData &wData) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_RECTANGLE_HPP
