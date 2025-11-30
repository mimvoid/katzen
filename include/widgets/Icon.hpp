#pragma once
#include <cstdint>
#include <optional>
#include <type_traits>
#include "../parts/icons.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
struct Icon : Widget {
  struct Builder;

  uint8_t icon;

  constexpr Icon(uint8_t icon, uint8_t scale = 1)
      : icon(icon), m_scale(scale < 1 ? 1 : scale) {}

  template <typename E>
  constexpr Icon(E icon, uint8_t scale = 1) {
    setIcon(icon);
    setScale(scale);
  }

  template <typename E>
  constexpr void setIcon(E iconId) {
    static_assert(std::is_enum_v<E>, "Given icon id type is an enum");
    icon = static_cast<std::underlying_type_t<E>>(iconId);
  }

  constexpr uint8_t scale() const { return m_scale; }
  constexpr void setScale(uint8_t value) { m_scale = value < 1 ? 1 : value; }

  void resize(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  constexpr int measureIcon() const { return m_scale * RAYGUI_ICON_SIZE; }

private:
  uint8_t m_scale{1};

public:
  struct Builder : WidgetBuilder<Builder> {
    constexpr Builder &icon(uint8_t value) {
      m_icon = value;
      return *this;
    }

    template <typename E>
    constexpr Builder &icon(E value) {
      static_assert(std::is_enum_v<E>, "Icon builder only accepts enum icons");
      m_icon = static_cast<std::underlying_type_t<E>>(value);
      return *this;
    }

    constexpr Builder &scale(uint8_t value) {
      m_scale = value < 1 ? 1 : value;
      return *this;
    }

    Icon build() const {
      Icon icon = m_scale ? Icon(m_icon, *m_scale) : Icon(m_icon);
      setWidgetProps(icon);
      return icon;
    }

  private:
    uint8_t m_icon{0};
    std::optional<uint8_t> m_scale{};
  };
};
} // namespace katzen
