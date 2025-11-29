#include "widgets/LabelEx.hpp"

namespace katzen {
void LabelEx::repaint(Gctx &g) {
  setBounds(g);
  reposition(g);

  textSize = style.measure(text);
  resize();
}

void LabelEx::draw(Dctx &d) { drawStyled(style, d.colors.text); }
} // namespace katzen
