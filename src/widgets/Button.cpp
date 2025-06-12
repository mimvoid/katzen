#include "Button.hpp"
#include <raylib.h>

namespace katzen::widgets {
void Button::color(ButtonState state) {
  GuiControlProperty border, base, text;

  switch (state) {
    case ButtonState::NORMAL:
      border = BORDER_COLOR_NORMAL;
      base = BASE_COLOR_NORMAL;
      text = TEXT_COLOR_NORMAL;
      break;
    case ButtonState::DISABLED:
      border = BORDER_COLOR_DISABLED;
      base = BASE_COLOR_DISABLED;
      text = TEXT_COLOR_DISABLED;
      break;
    case ButtonState::FOCUSED:
      border = BORDER_COLOR_FOCUSED;
      base = BASE_COLOR_FOCUSED;
      text = TEXT_COLOR_FOCUSED;
      break;
    case ButtonState::PRESSED:
      border = BORDER_COLOR_PRESSED;
      base = BASE_COLOR_PRESSED;
      text = TEXT_COLOR_PRESSED;
      break;
    default:
      break;
  }

  m_colors.border = GetColor(GuiGetStyle(DEFAULT, border));
  m_colors.base = GetColor(GuiGetStyle(DEFAULT, base));
  m_colors.text = GetColor(GuiGetStyle(DEFAULT, text));
}

float Button::measureSize(Axis axis) const {
  const float size = child->size(axis) + padding.get(axis) + (2 * borderWidth);
  return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
}

void Button::repaint(Gctx g) {
  externalBounds.x = g.w;
  externalBounds.y = g.h;

  position(g);

  g.pad(padding);
  child->repaint(g);

  updateSize();
}

void Button::updateState() {
  if (m_state == ButtonState::DISABLED)
    return; // Nothing to do

  const ButtonState prevState = m_state;

  if (CheckCollisionPointRec(GetMousePosition(), rlRectangle(rect()))) {
    m_state = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? ButtonState::PRESSED
                                                  : ButtonState::FOCUSED;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && callback)
      callback();
  } else {
    m_state = ButtonState::NORMAL;
  }

  if (m_state != prevState) {
    color(m_state); // The state changed, update colors
  }
}

void Button::draw(glm::vec2 p) {
  updateState();

  const Rectangle box = rlRectangle(rect());
  DrawRectangleRec(box, m_colors.base);
  if (borderWidth != 0) {
    DrawRectangleLinesEx(box, borderWidth, m_colors.border);
  }

  child->draw({p.x - x() + child->x(), p.y - y() + child->y()});
}
} // namespace katzen::widgets
