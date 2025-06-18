#include "Widget.hpp"

namespace katzen {
void Widget::repaint(Gctx g) {
  setExternalBounds(g);
  reposition(g);
  resize();
}

float Widget::measure(Axis axis) const {
  return std::clamp(padding.get(axis), (int)minSize(axis), (int)maxSize(axis));
}
} // namespace katzen
