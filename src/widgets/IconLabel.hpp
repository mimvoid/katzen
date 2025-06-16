#pragma once
#include <functional>
#include "Icon.hpp"
#include "Label.hpp"

namespace katzen {
struct IconLabel : Widget {
  const static int spacing = 4;
  Icon icon;
  Label label;

  IconLabel(uint8_t iconId,
            std::string_view text,
            std::size_t fontId = theme::defaultFontId(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>());

  template <typename E>
  IconLabel(E enumIconId,
            std::string_view text,
            std::size_t fontId = theme::defaultFontId(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>())
      : icon(enumIconId), label(text, fontId) {
    if (setup) setup(*this);
  }

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen
