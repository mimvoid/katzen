#include "Slider.hpp"
#include <raylib.h>
#include "../components/scales.hpp"
#include "../theming/fonts.hpp"

namespace katzen {
Slider::Slider(float initialValue,
               Axis direction,
               float sizeScale,
               std::function<void(float)> callback,
               std::function<void(Slider &)> setup)
    : direction(direction), callback(callback), m_sizeScale(sizeScale) {
  value(initialValue);
  if (setup) setup(*this);
}

void Slider::draw() {
  Widget::draw();
  const Rectangle box = rlRectangle(rect());

  const float gap = m_borderWidth * 2;
  const Rectangle trough{
      box.x + gap, box.y + gap, box.width - (2 * gap), box.height - (2 * gap)};

  if (!m_dragging) {
    updateState(box);

    // Store the dragging state, such that the slider still responds when the
    // mouse leaves the slider if the left mouse button has not been released.
    if (m_state == State::ACTIVE) m_dragging = true;
  }

  if (m_dragging) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      m_dragging = false;
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

    newValue = glm::clamp(newValue, 0.0f, 1.0f);
    if (newValue != prevValue) {
      m_value = newValue;
      if (callback) callback(newValue);
    }
  }

  // Drawing the slider
  DrawRectangleRec(box, m_colors.base);                      // base
  DrawRectangleLinesEx(box, m_borderWidth, m_colors.border); // border

  if (m_value == 0.0f) {
    return; // no trough to draw
  }
  if (m_value == 1.0f) {
    DrawRectangleRec(trough, m_colors.border);
    return;
  }

  Rectangle filledTrough = trough;

  if (direction == Axis::X) {
    filledTrough.width *= value();
  } else {
    filledTrough.height *= value();
    filledTrough.y += trough.height - filledTrough.height;
  }

  DrawRectangleRec(filledTrough, m_colors.border);
}

float Slider::measureSize(Axis axis) const {
  const float size =
      padding.get(axis)
      + (m_sizeScale * theme::getFontSize() * ((axis == direction) ? 4 : 1));

  return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
}
} // namespace katzen
