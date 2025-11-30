#include "widgets/Icon.hpp"

namespace katzen {
void Icon::resize(Gctx g) {
  const float iconSize = measureIcon();
  m_rect.w = g.clampWidth(padding.getX() + iconSize);
  m_rect.h = g.clampHeight(padding.getY() + iconSize);
}

void Icon::draw(Dctx &d) {
  drawIcon(icon,
           x() + padding.left,
           y() + padding.top,
           m_scale * d.theme.iconSize,
           (Color)d.colors().text);
}
} // namespace katzen
