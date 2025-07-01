#pragma once
#include <cstdint>
#include <type_traits>
#include "../components/icons.hpp"
#include "../theme.hpp"
#include "Widget.hpp"

namespace katzen {
struct Icon : Widget {
  friend struct IconLabel;

  constexpr Icon(uint8_t id, uint8_t iconScale = theme::theme.iconSize)
      : m_iconId(id), m_scale(iconScale >= 1 ? iconScale : 1) {}

  template <typename E>
  Icon(E iconEnumId, uint8_t iconScale = theme::theme.iconSize) {
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
  constexpr void scale(uint8_t size) { m_scale = size >= 1 ? size : 1; }

  constexpr int measureIcon() const { return m_scale * RAYGUI_ICON_SIZE; }

  void draw(Dctx &d) override {
    drawIcon(m_iconId,
             x() + padding.left,
             y() + padding.top,
             m_scale * d.iconSize,
             d.colors.text);
  }

protected:
  float measure(Axis axis) const override {
    return padding.get(axis) + measureIcon();
  }

private:
  uint8_t m_iconId;
  uint8_t m_scale;
};
} // namespace katzen
