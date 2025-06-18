#include "Checkbox.hpp"
#include "../theme/fonts.hpp"

namespace katzen {
void Checkbox::draw(Dctx &d) {
  const Rectangle box = m_rect;

  if (updateState(d, box)) {
    checked = !checked;
    if (callback) callback(checked);
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
  const float size = (m_scale * theme::getFontSize()) + padding.get(axis);
  return clampSize(size, axis);
}
} // namespace katzen
