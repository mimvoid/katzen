#include "widgets/Widget.hpp"
#include <algorithm>

namespace katzen {
void Widget::repaint(Gctx g) {
  setBounds(g);
  reposition(g);
  resize();
}

float Widget::measure(Axis axis) const {
  return std::clamp(
      padding.getSum(axis), (int)minSize.get(axis), (int)m_bounds.get(axis));
}
} // namespace katzen
