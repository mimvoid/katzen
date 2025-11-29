#include "widgets/Icon.hpp"

namespace katzen {
void Icon::draw(Dctx &d) {
  drawIcon(icon,
           x() + padding.left,
           y() + padding.top,
           m_scale * d.theme.iconSize,
           (Color)d.colors().text);
}

float Icon::measure(Axis axis) const {
  return padding.getSum(axis) + measureIcon();
}
} // namespace katzen
