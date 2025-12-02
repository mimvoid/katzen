#include "widgets/Slider.hpp"
#include <raylib.h>
#include <algorithm>
#include "parts/scales.hpp"

namespace katzen {
void Slider::resize(Gctx g) {
  const float troughThickness = m_sizeScale * g.font.size();

  const float dirSize =
      g.clampSize(padding.getSum(direction) + troughThickness * 4, direction);

  const float flipSize = g.clampSize(
      padding.getSum(flip(direction)) + troughThickness, flip(direction));

  m_rect.setSizes(direction, dirSize, flipSize);
}

void Slider::draw(Dctx &d) {
  const Rectangle box = (Rectangle)m_rect;

  const float gap = d.theme.borderWidth * 2;
  const Rectangle trough{
      box.x + gap, box.y + gap, box.width - (2 * gap), box.height - (2 * gap)};

  if (!m_dragging) {
    updateState(d, box);

    // Store the dragging state, such that the slider still responds when the
    // mouse leaves the slider if the left mouse button has not been released.
    if (m_state == State::ACTIVE) m_dragging = true;
  }

  StateColors colors = d.colors();

  if (m_dragging) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      m_dragging = false;
    }

    d.cursor = MOUSE_CURSOR_POINTING_HAND;

    if (d.state != State::ACTIVE) {
      // Even if the state isn't active, use the active colors anyway
      colors = d.theme.active;
    }

    // Update the slider value
    const Vector2 mousePos = GetMousePosition();
    const float prevValue = value();
    float newValue;

    switch (direction) {
    case Axis::X:
      newValue = toScaledValue(mousePos.x, trough.x, trough.x + trough.width);
      break;
    case Axis::Y:
      newValue = toScaledValue(mousePos.y, trough.y, trough.y + trough.height);
      break;
    }

    newValue = std::clamp(newValue, 0.0f, 1.0f);
    if (newValue != prevValue) {
      m_value = newValue;
      if (onValueChange) onValueChange(newValue);
    }
  }

  // Drawing the slider
  DrawRectangleRec(box, (Color)colors.base); // base
  if (d.theme.borderWidth != 0) {
    DrawRectangleLinesEx(
        box, d.theme.borderWidth, (Color)colors.border); // border
  }

  if (m_value == 0.0f) {
    return; // no trough to draw
  }
  if (m_value == 1.0f) {
    DrawRectangleRec(trough, (Color)colors.border);
    return;
  }

  Rectangle filledTrough = trough;

  if (direction == Axis::X) {
    filledTrough.width *= value();
  } else {
    filledTrough.height *= value();
    filledTrough.y += trough.height - filledTrough.height;
  }

  DrawRectangleRec(filledTrough, (Color)colors.border);
}
} // namespace katzen
