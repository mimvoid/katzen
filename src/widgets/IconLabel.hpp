#pragma once
#include <functional>
#include "Icon.hpp"
#include "Label.hpp"

namespace katzen {
struct IconLabel : Widget {
  int spacing;
  Icon icon;
  Label label;

  IconLabel(uint8_t iconId,
            std::string_view text,
            theme::FontStyle &style = theme::getFontStyle(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>());

  template <typename E>
  IconLabel(E enumIconId,
            std::string_view text,
            theme::FontStyle &style = theme::getFontStyle(),
            std::function<void(IconLabel &)> setup =
                std::function<void(IconLabel &)>())
      : spacing(style.fontSize() / 4), icon(enumIconId), label(text, style) {
    if (setup) setup(*this);
  }

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;
};
} // namespace katzen
