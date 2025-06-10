#pragma once
#include <raygui.h>
#include "Widget.hpp"

#ifndef RAYGUI_ICON_SIZE
#define RAYGUI_ICON_SIZE 16
#endif

namespace katzen::widgets {
struct Icon : Widget {
  int iconId;
  Color color;

  Icon(int iconId)
      : iconId(iconId),
        color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))),
        _iconSize(1) {}

  Icon(int iconId, int iconSize)
      : iconId(iconId),
        color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))) {
    this->iconSize(iconSize);
  }

  constexpr int iconSize() const { return _iconSize; }
  constexpr void iconSize(int size) { _iconSize = glm::max(1, size); }

  constexpr int measureIcon() const {
    return empty() ? 0 : _iconSize * RAYGUI_ICON_SIZE;
  }

  // Check whether there is no icon to be drawn
  // TODO: Consider the actual icon's bitset
  constexpr bool empty() const { return iconId == ICON_NONE; }

  void draw(glm::vec2 p) override {
    if (!empty()) {
      GuiDrawIcon(
          iconId, p.x + padding.left, p.y + padding.top, _iconSize, color);
    }
  }

protected:
  float measureSize(Axis axis) const override {
    return padding.get(axis) + measureIcon();
  }

private:
  int _iconSize;
};
} // namespace katzen::widgets
