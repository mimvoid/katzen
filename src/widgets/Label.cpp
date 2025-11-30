#include "widgets/Label.hpp"
#include <cmath>
#include "parts/textHelpers.hpp"

namespace katzen {
void Label::resize(Gctx g) {
  const Vec2 textSize = g.font.measure(text);
  m_rect.w = g.clampWidth(padding.getX() + textSize.x);

  float height = padding.getY() + textSize.y;

  if (willWrap(textSize.x, g.w)) {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines = std::ceil(textSize.x / (g.w - padding.getX()));
    height += textSize.y * (lines - 1);
  }

  m_rect.h = g.clampHeight(height);
}

void Label::draw(Dctx &d) { drawStyled(d.font, (Color)d.colors().text); }

void Label::drawStyled(FontStyle &style, Color textColor) {
  if (empty()) return;

  const Vector2 p{m_rect.x + padding.left, m_rect.y + padding.top};

  if (wrapWords && style.measure(text).x > m_rect.w - padding.getX()) {
    drawTextBoxed(
        style.font,
        text,
        {p.x, p.y, m_rect.w - padding.getX(), m_rect.h - padding.getY()},
        style.size(),
        style.spacing,
        textColor);
  } else {
    DrawTextEx(style.font, text, p, style.size(), style.spacing, textColor);
  }
}
} // namespace katzen
