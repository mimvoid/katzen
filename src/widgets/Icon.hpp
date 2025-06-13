#pragma once
#include <cstdint>
#include <type_traits>
#include "../components/icons.hpp"
#include "../theming/themer.hpp"
#include "Widget.hpp"

namespace katzen::widgets {
struct Icon : Widget {
  Color color;

  Icon(uint8_t id, uint8_t size)
      : color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)) {
    iconId(id);
    iconSize(size);
  }

  template <typename E>
  Icon(E iconEnumId, uint8_t size)
      : Icon(static_cast<uint8_t>(iconEnumId), size) {}

  Icon(uint8_t iconId)
      : Icon(iconId, theme::getProperty(theme::UIntProp::ICON_SIZE)) {}

  template <typename E>
  Icon(E iconEnumId) : Icon(static_cast<uint8_t>(iconEnumId)) {}

  constexpr uint8_t iconId() const { return m_iconId; }
  constexpr void iconId(uint8_t id) { m_iconId = id; }

  template <typename E>
  constexpr void iconId(E enumId) {
    static_assert(std::is_enum_v<E>, "Given icon id type is an enum");
    m_iconId = static_cast<std::underlying_type_t<E>>(enumId);
  }

  constexpr uint8_t iconSize() const { return m_iconSize; }
  constexpr void iconSize(int size) { m_iconSize = glm::max(1, size); }

  constexpr int measureIcon() const {
    return empty() ? 0 : m_iconSize * RAYGUI_ICON_SIZE;
  }

  // Check whether there is no icon to be drawn
  // TODO: Consider the actual icon's bitset
  constexpr bool empty() const { return iconId() == 0; }

  void draw(glm::vec2 p) override {
    if (!empty()) {
      drawIcon(
          iconId(), p.x + padding.left, p.y + padding.top, m_iconSize, color);
    }
  }

protected:
  float measureSize(Axis axis) const override {
    return padding.get(axis) + measureIcon();
  }

private:
  uint8_t m_iconId;
  uint8_t m_iconSize;
};
} // namespace katzen::widgets
