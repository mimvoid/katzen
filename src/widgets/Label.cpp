#include "widgets/Label.hpp"
#include <cmath>
#include "parts/textHelpers.hpp"

namespace katzen {
float Label::measure(Axis axis) const {
  float size = padding.getSum(axis);

  if (axis == Axis::X || !willWrap()) {
    size += textSize.get(axis);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        std::ceil(textSize.x / (maxWidth() - padding.getSum(Axis::X)));

    size += textSize.y * lines;
  }

  return clampSize(size, axis);
}

void Label::repaint(Gctx &g) {
  setBounds(g);
  reposition(g);

  textSize = g.font.measure(text);
  resize();
}

void Label::draw(Dctx &d) { drawStyled(d.font, d.colors.text); }

void Label::drawStyled(FontStyle &style, Color textColor) {
  if (empty()) return;

  const Vector2 p{x() + padding.left, y() + padding.top};

  if (willWrap()) {
    drawTextBoxed(style.font,
                  text,
                  {p.x,
                   p.y,
                   m_rect.w - padding.getSum(Axis::X),
                   m_rect.h - padding.getSum(Axis::Y)},
                  style.size(),
                  style.spacing,
                  textColor);
  } else {
    DrawTextEx(style.font, text, p, style.size(), style.spacing, textColor);
  }
}
} // namespace katzen
