#include "widgets/Slider.hpp"
#include <raylib.h>
#include "parts/scales.hpp"

namespace katzen {
void Slider::resize(Gctx g) {
  const float troughThickness = m_sizeScale * g.font.size();

  const float dirSize =
    g.clampSize(padding.getSum(direction) + troughThickness * 4, direction);

  const float flipSize =
    g.clampSize(padding.getSum(!direction) + troughThickness, !direction);

  m_rect.setSizes(direction, dirSize, flipSize);
}

void Slider::draw(Dctx &d) {
  const Rectangle rec(m_rect);

  const float gap = d.theme.borderWidth * 2;
  const Rectangle trough{
    rec.x + gap, rec.y + gap, rec.width - (2 * gap), rec.height - (2 * gap)
  };

  const bool pressReleased = updateState(d, rec);

  // Update the slider value
  if (enabled && (m_locked || pressReleased)) {
    const float prevValue = m_value;
    const Vector2 mousePos = GetMousePosition();

    if (direction == Axis::X)
      setValue(toScaledValue(mousePos.x, trough.x, trough.x + trough.width));
    else
      setValue(toScaledValue(mousePos.y, trough.y, trough.y + trough.height));

    if (pressReleased && onValueUpdate) {
      onValueUpdate(*this, prevValue);
    }
  }

  const Color border(d.colors().border);

  // Drawing the slider
  DrawRectangleRec(rec, (Color)d.colors().base); // base
  if (d.theme.borderWidth != 0) {
    DrawRectangleLinesEx(rec, d.theme.borderWidth, border); // border
  }

  if (m_value == 0.0f) {
    return; // no trough to draw
  }
  if (m_value == 1.0f) {
    DrawRectangleRec(trough, border);
    return;
  }

  Rectangle filledTrough = trough;

  if (direction == Axis::X) {
    filledTrough.width *= m_value;
  } else {
    filledTrough.height *= m_value;
    filledTrough.y += trough.height - filledTrough.height;
  }

  DrawRectangleRec(filledTrough, border);
}
} // namespace katzen
