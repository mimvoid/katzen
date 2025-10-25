#include "../../include/widgets/Widget.hpp"

namespace katzen {
void Widget::repaint(Gctx g) {
  setBounds(g);
  reposition(g);
  resize();
}

float Widget::measure(Axis axis) const {
  return std::clamp(
      padding.getSum(axis), (int)get(minSize, axis), (int)get(m_bounds, axis));
}
} // namespace katzen
