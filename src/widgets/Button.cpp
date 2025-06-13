#include "Button.hpp"
#include <raylib.h>

namespace katzen::widgets {
void Button::disable() {
  if (m_state == State::DISABLED) return; // nothing to do

  m_state = State::DISABLED;

  // Disabled state doesn't update its colors when drawing,
  // so get the colors beforehand
  m_colors = theme::getStateColors(State::DISABLED);
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
  if (m_state == State::DISABLED) return; // Nothing to do

  const State prevState = m_state;

  if (CheckCollisionPointRec(GetMousePosition(), rlRectangle(rect()))) {
    m_state = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? State::ACTIVE
                                                   : State::FOCUS;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && callback) callback();
  } else {
    m_state = State::NORMAL;
  }

  if (m_state != prevState) {
    // The state changed, update colors
    m_colors = theme::getStateColors(m_state);
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
