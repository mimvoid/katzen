#include "Checkbox.hpp"
#include "../theming/fonts.hpp"

namespace katzen {
void Checkbox::draw() {
  Widget::draw();
  const Rectangle box = rlRectangle(rect());

  if (updateState(box)) {
    checked = !checked;
    if (callback) callback(checked);
  }

  DrawRectangleRec(box, m_colors.base);
  DrawRectangleLinesEx(box, m_borderWidth, m_colors.border);

  if (checked) {
    const float gap = m_borderWidth * 2;
    DrawRectangleRec({box.x + gap,
                      box.y + gap,
                      box.width - (2 * gap),
                      box.height - (2 * gap)},
                     m_colors.border);
  }
}

float Checkbox::measureSize(Axis axis) const {
  const float size = (m_scale * theme::getFontSize()) + padding.get(axis);
  return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
}
} // namespace katzen
