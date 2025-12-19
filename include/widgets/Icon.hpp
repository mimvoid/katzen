#ifndef KATZE_WIDGETS_ICON_HPP
#define KATZE_WIDGETS_ICON_HPP

#include <cstdint>
#include "../icons.hpp"
#include "Widget.hpp"

namespace katze {
struct Icon : Widget {
  IconBits bits{};

  Icon(const IconBits &bits, uint8_t scale = 1)
    : bits(bits), m_scale(scale < 1 ? 1 : scale) {}

  constexpr uint8_t scale() const { return m_scale; }
  constexpr void setScale(uint8_t value) { m_scale = value < 1 ? 1 : value; }

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;

private:
  uint8_t m_scale{1};
};
} // namespace katze

#endif // !KATZE_WIDGETS_ICON_HPP
