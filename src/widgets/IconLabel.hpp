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
            const Font &font,
            std::string_view text,
            float size,
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>());

  template <typename E>
  IconLabel(E enumIconId,
            const Font &font,
            std::string_view text,
            float size,
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>())
      : icon(enumIconId), label(font, text, size) {
    if (setup) setup(*this);
  }

  IconLabel(uint8_t iconId,
            std::string_view text,
            std::size_t fontIndex = theme::defaultFontId(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>());

  template <typename E>
  IconLabel(E enumIconId,
            std::string_view text,
            std::size_t fontIndex = theme::defaultFontId(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>())
      : icon(enumIconId), label(text, fontIndex) {
    if (setup) setup(*this);
  }

  void repaint(Gctx g) override;
  void draw() override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen
