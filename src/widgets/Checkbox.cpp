#include "widgets/Checkbox.hpp"

namespace katzen {
void Checkbox::resize(Gctx g) {
  const float checkSize = m_scale * g.font.size();
  m_rect.w = g.clampWidth(checkSize + padding.getX());
  m_rect.h = g.clampHeight(checkSize + padding.getY());
}

void Checkbox::draw(Dctx &d) {
  const Rectangle rec(m_rect);

  if (updateState(d, rec)) {
    checked = !checked;
    if (onCheck) onCheck(checked);
  }

  const StateColors &colors = d.colors();

  DrawRectangleRec(rec, (Color)colors.base);
  if (d.theme.borderWidth != 0) {
    DrawRectangleLinesEx(rec, d.theme.borderWidth, (Color)colors.border);
  }

  if (checked) {
    const float gap = d.theme.borderWidth * 2;
    DrawRectangleRec({rec.x + gap,
                      rec.y + gap,
                      rec.width - (2 * gap),
                      rec.height - (2 * gap)},
                     (Color)colors.border);
  }
}
} // namespace katzen
