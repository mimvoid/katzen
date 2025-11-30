#include "widgets/LabelEx.hpp"
#include <cmath>

namespace katzen {
void LabelEx::resize(Gctx g) {
  const Vec2 textSize = style.measure(text);
  m_rect.w = g.clampWidth(padding.getX() + textSize.x);

  float height = padding.getY() + textSize.y;
  if (willWrap(textSize.x, g.w)) {
    const int lines = std::ceil(textSize.x / (g.w - padding.getX()));
    height += textSize.y * (lines - 1);
  }

  m_rect.h = g.clampHeight(height);
}

void LabelEx::draw(Dctx &d) { drawStyled(style, (Color)d.colors().text); }
} // namespace katzen
