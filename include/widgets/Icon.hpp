#pragma once
#include <cstdint>
#include <optional>
#include <type_traits>
#include "../parts/icons.hpp"
#include "../theme.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
struct Icon : Widget {
  friend struct IconLabel;

  struct Builder : WidgetBuilder {
    constexpr Builder() = default;

    Builder &icon(uint8_t value) {
      m_icon = value;
      return *this;
    }

    template <typename E>
    Builder &icon(E value) {
      static_assert(std::is_enum_v<E>, "Icon builder only accepts enum icons");
      m_icon = static_cast<std::underlying_type_t<E>>(value);
      return *this;
    }

    Builder &scale(uint8_t value) {
      m_scale = std::max((uint8_t)1, value);
      return *this;
    }

    Icon build() const {
      Icon icon = m_scale ? Icon(m_icon, *m_scale) : Icon(m_icon);
      setWidgetProps(icon);
      return icon;
    }

  private:
    uint8_t m_icon = 0;
    std::optional<uint8_t> m_scale{};
  };

  uint8_t icon;

  constexpr Icon(uint8_t icon, uint8_t scale = theme::theme.iconSize)
      : icon(icon), m_scale(std::max((uint8_t)1, scale)) {}

  template <typename E>
  Icon(E icon, uint8_t scale = theme::theme.iconSize) {
    setIcon(icon);
    setScale(scale);
  }

  template <typename E>
  constexpr void setIcon(E iconId) {
    static_assert(std::is_enum_v<E>, "Given icon id type is an enum");
    icon = static_cast<std::underlying_type_t<E>>(iconId);
  }

  constexpr uint8_t scale() const { return m_scale; }
  constexpr void setScale(uint8_t value) {
    m_scale = std::max((uint8_t)1, value);
  }

  void draw(Dctx &d) override {
    drawIcon(icon,
             x() + padding.left,
             y() + padding.top,
             m_scale * d.iconSize,
             d.colors.text);
  }

protected:
  float measure(Axis axis) const override {
    return padding.getSum(axis) + measureIcon();
  }

  constexpr int measureIcon() const { return m_scale * RAYGUI_ICON_SIZE; }

private:
  uint8_t m_scale;
};
} // namespace katzen
