#include "Text.hpp"

Text::Text(const Font &font, std::string_view text, float size)
    : font(font),
      text(text),
      color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))),
      fontSize(size),
      fontSpacing(GuiGetStyle(DEFAULT, TEXT_SPACING)) {}
