#include "widgets/Checkbox.hpp"

namespace katzen {
void Checkbox::repaint(Gctx &g) {
  m_fontSize = g.font.size();
  Widget::repaint(g);
}

void Checkbox::draw(Dctx &d) {
  const Rectangle box = (Rectangle)m_rect;

  if (updateState(d, box)) {
    checked = !checked;
    if (onCheck) onCheck(checked);
  }

  DrawRectangleRec(box, d.colors.base);
  if (d.borderWidth != 0) {
    DrawRectangleLinesEx(box, d.borderWidth, d.colors.border);
  }

  if (checked) {
    const float gap = d.borderWidth * 2;
    DrawRectangleRec({box.x + gap,
                      box.y + gap,
                      box.width - (2 * gap),
                      box.height - (2 * gap)},
                     d.colors.border);
  }
}

float Checkbox::measure(Axis axis) const {
  const float size = (m_scale * m_fontSize) + padding.getSum(axis);
  return clampSize(size, axis);
}
} // namespace katzen
