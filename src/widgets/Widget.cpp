#include "Widget.hpp"
#include <climits>

namespace katzen::widgets {
Widget::Widget()
    : padding{0, 0, 0, 0},
      expand{false, false},
      bounds{{0, 0}, {INT_MAX, INT_MAX}},
      externalBounds{GetRenderWidth(), GetRenderHeight()} {}

void Widget::repaint(Gctx g) {
  externalBounds.x = g.w;
  externalBounds.y = g.h;

  position(g);
  updateSize();
}
} // namespace katzen::widgets
