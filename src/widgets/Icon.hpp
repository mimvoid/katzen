#pragma once
#include <cstdint>
#include <type_traits>
#include "../components/icons.hpp"
#include "../theming/themer.hpp"
#include "Widget.hpp"

namespace katzen {
struct Icon : Widget {
  friend struct IconLabel;

  Icon(uint8_t id,
       uint8_t iconScale = theme::getProperty(theme::UIntProp::ICON_SIZE)) {
    setId(id);
    scale(iconScale);
  }

  template <typename E>
  Icon(E iconEnumId,
       uint8_t iconScale = theme::getProperty(theme::UIntProp::ICON_SIZE)) {
    setId(iconEnumId);
    scale(iconScale);
  }

  constexpr uint8_t getId() const { return m_iconId; }
  constexpr void setId(uint8_t id) { m_iconId = id; }

  template <typename E>
  constexpr void setId(E enumId) {
    static_assert(std::is_enum_v<E>, "Given icon id type is an enum");
    m_iconId = static_cast<std::underlying_type_t<E>>(enumId);
  }

  constexpr uint8_t scale() const { return m_scale; }
  constexpr void scale(int size) { m_scale = glm::max(1, size); }

  constexpr int measureIcon() const { return m_scale * RAYGUI_ICON_SIZE; }

  void draw(Dctx &d) override {
    drawIcon(m_iconId,
             x() + padding.left,
             y() + padding.top,
             m_scale * d.iconSize,
             d.colors.text);
  }

protected:
  float measureSize(Axis axis) const override {
    return padding.get(axis) + measureIcon();
  }

private:
  uint8_t m_iconId;
  uint8_t m_scale;
};
} // namespace katzen
