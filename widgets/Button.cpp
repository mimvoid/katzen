#include "../widgets.hpp"
#include <algorithm>
#include <raylib.h>

Button::Button(std::unique_ptr<Widget> &&child) : child(std::move(child)) {
  init();
}
Button::Button(std::unique_ptr<Widget> &&child, void (*clickAction)(void))
    : child(std::move(child)), action(clickAction) {
  init();
}

void Button::init() {
  state = STATE_NORMAL;
  borderWidth = GuiGetStyle(BUTTON, BORDER_WIDTH);
  setPadding(8);

  colors.border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
  colors.base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));
  colors.text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
}

GuiState Button::getState() const { return this->state; }

void Button::enable() {
  if (state == STATE_DISABLED) {
    state = STATE_NORMAL;
  }
}
void Button::disable() {
  if (state == STATE_DISABLED)
    return; // nothing to do

  state = STATE_DISABLED;

  // Disabled state doesn't update its colors when drawing,
  // so get the colors beforehand
  colors.border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_DISABLED));
  colors.base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_DISABLED));
  colors.text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_DISABLED));
}
void Button::toggleEnabled() { state == STATE_DISABLED ? enable() : disable(); }

void Button::setClickAction(void (*clickAction)(void)) {
  this->action = clickAction;
}

float Button::measureSize(Axis a) const {
  const float size = child->getSize(a) + getTotalPadding(a) + (2 * borderWidth);
  return std::clamp(size, (float)getMinSize(a), (float)getMaxSize(a));
}

void Button::repaint(Gctx g) {
  setExternalBounds(g.bounds);
  setPosition(g.p);

  pad(g);
  child->repaint(g);

  updateWidth();
  updateHeight();
}

void Button::updateState() {
  if (state == STATE_DISABLED)
    return; // Nothing to do

  const GuiState prevState = state;

  if (CheckCollisionPointRec(GetMousePosition(), getBox())) {
    state =
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? STATE_PRESSED : STATE_FOCUSED;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && action)
      action();
  } else {
    state = STATE_NORMAL;
  }

  if (state == prevState)
    return;

  // The state changed, update colors
  switch (state) {
    case STATE_NORMAL:
      colors.border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
      colors.base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));
      colors.text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
      break;
    case STATE_FOCUSED:
      colors.border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_FOCUSED));
      colors.base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_FOCUSED));
      colors.text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_FOCUSED));
      break;
    case STATE_PRESSED:
      colors.border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_PRESSED));
      colors.base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_PRESSED));
      colors.text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_PRESSED));
      break;
    default:
      break;
  }
}

void Button::draw(Vector2 p) {
  updateState();

  const Rectangle box = getBox();
  DrawRectangleRec(box, colors.base);
  if (borderWidth != 0) {
    DrawRectangleLinesEx(box, borderWidth, colors.border);
  }

  child->draw({p.x - getX() + child->getX(), p.y - getY() + child->getY()});
}
