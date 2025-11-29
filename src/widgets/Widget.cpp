#include "widgets/Widget.hpp"
#include <algorithm>

namespace katzen {
void Widget::repaint(Gctx &g) {
  setBounds(g);
  reposition(g);
  resize();
}

void Widget::translate(float dx, float dy) {
  m_rect.x += dx;
  m_rect.y += dy;
}

float Widget::measure(Axis axis) const {
  return std::clamp(
      padding.getSum(axis), (int)minSize.get(axis), (int)m_bounds.get(axis));
}
} // namespace katzen
