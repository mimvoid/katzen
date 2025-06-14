#include "Text.hpp"
#include <glm/ext/scalar_common.hpp>
#include "../theming/themer.hpp"

namespace katzen {
Text::Text(const Font &font, std::string_view text, float size)
    : content(text),
      font(font),
      fontSpacing(0.0f),
      color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)) {
  fontSize(size);
  updateSize();
}

Text::Text(const Font &font, std::string_view text)
    : Text(font, text, font.baseSize) {}
} // namespace katzen
