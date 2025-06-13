#pragma once
#include <raygui.h>
#include "../theming/themer.hpp"
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
        color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)),
        m_iconSize(theme::getProperty(theme::UIntProp::ICON_SIZE)) {}

  Icon(int iconId, int iconSize)
      : iconId(iconId),
        color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)) {
    this->iconSize(iconSize);
  }

  constexpr int iconSize() const { return m_iconSize; }
  constexpr void iconSize(int size) { m_iconSize = glm::max(1, size); }

  constexpr int measureIcon() const {
    return empty() ? 0 : m_iconSize * RAYGUI_ICON_SIZE;
  }

  // Check whether there is no icon to be drawn
  // TODO: Consider the actual icon's bitset
  constexpr bool empty() const { return iconId == ICON_NONE; }

  void draw(glm::vec2 p) override {
    if (!empty()) {
      GuiDrawIcon(
          iconId, p.x + padding.left, p.y + padding.top, m_iconSize, color);
    }
  }

protected:
  float measureSize(Axis axis) const override {
    return padding.get(axis) + measureIcon();
  }

private:
  int m_iconSize;
};
} // namespace katzen::widgets
