#include "../widgets.hpp"

#ifndef RAYGUI_ICON_SIZE
#define RAYGUI_ICON_SIZE 16
#endif

Icon::Icon(GuiIconName iconName)
    : iconName(iconName),
      color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))), iconSize(1) {}

Icon::Icon(GuiIconName iconName, int iconSize)
    : iconName(iconName),
      color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))) {
  setIconSize(iconSize);
}

int Icon::getIconSize() const { return iconSize; }
void Icon::setIconSize(int size) { iconSize = (size > 0) ? size : 1; }

bool Icon::isEmpty() const { return iconName == ICON_NONE; }

int Icon::measureIconSize() const { return isEmpty() ? 0 : iconSize * RAYGUI_ICON_SIZE; }
float Icon::measureSize(Axis a) const {
  return getTotalPadding(a) + measureIconSize();
}

void Icon::draw(Vector2 p) {
  if (!isEmpty()) {
    GuiDrawIcon(iconName, p.x + padding.left, p.y + padding.top, iconSize, color);
  }
}
