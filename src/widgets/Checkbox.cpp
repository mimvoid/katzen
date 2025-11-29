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

  const StateColors &colors = d.colors();

  DrawRectangleRec(box, colors.base);
  if (d.theme.borderWidth != 0) {
    DrawRectangleLinesEx(box, d.theme.borderWidth, colors.border);
  }

  if (checked) {
    const float gap = d.theme.borderWidth * 2;
    DrawRectangleRec({box.x + gap,
                      box.y + gap,
                      box.width - (2 * gap),
                      box.height - (2 * gap)},
                     colors.border);
  }
}

float Checkbox::measure(Axis axis) const {
  const float size = (m_scale * m_fontSize) + padding.getSum(axis);
  return clampSize(size, axis);
}
} // namespace katzen
