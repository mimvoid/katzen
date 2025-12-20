#ifndef KATZE_WIDGETS_LABELEX_HPP
#define KATZE_WIDGETS_LABELEX_HPP

#include "../Font.hpp"
#include "Label.hpp"

namespace katze {
struct LabelEx : Label {
  Font font{};

  LabelEx(Font font = {}, const char *text = "", bool willWrap = true)
    : Label(text, willWrap), font(font) {}

  void resize(Gctx g, FRect &rect) override { resizeForFont(font, g, rect); }
  void view(Dctx &d, FRect rect) override { viewForFont(font, d, rect); }
};
} // namespace katze

#endif // !KATZE_WIDGETS_LABELEX_HPP
