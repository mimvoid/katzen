#include "widgets/Checkbox.hpp"

namespace katzen {
void Checkbox::resize(Gctx g) {
  const float checkSize = m_scale * g.font.size();
  m_rect.w = g.clampWidth(checkSize + padding.getX());
  m_rect.h = g.clampHeight(checkSize + padding.getY());
}

void Checkbox::draw(Dctx &d) {
  const Rectangle box = (Rectangle)m_rect;

  if (updateState(d, box)) {
    checked = !checked;
    if (onCheck) onCheck(checked);
  }

  const StateColors &colors = d.colors();

  DrawRectangleRec(box, (Color)colors.base);
  if (d.theme.borderWidth != 0) {
    DrawRectangleLinesEx(box, d.theme.borderWidth, (Color)colors.border);
  }

  if (checked) {
    const float gap = d.theme.borderWidth * 2;
    DrawRectangleRec({box.x + gap,
                      box.y + gap,
                      box.width - (2 * gap),
                      box.height - (2 * gap)},
                     (Color)colors.border);
  }
}
} // namespace katzen
