#include "Text.hpp"
#include <glm/ext/scalar_common.hpp>
#include "../theming/fonts.hpp"
#include "../theming/themer.hpp"

namespace katzen {
Text::Text(const Font &font, std::string_view content, float size)
    : content(content),
      font(font),
      color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)) {
  fontSize(size);
  updateSize();
}

Text::Text(const Font &font, std::string_view content)
    : Text(font, content, font.baseSize) {}

Text::Text(std::string_view content, std::size_t fontIndex)
    : content(content),
      font(theme::getFont(fontIndex)),
      color(theme::getProperty(theme::ColorProp::NORMAL_TEXT)) {
  const theme::ThemeFont &themeFont = theme::getThemeFont(fontIndex);
  m_fontSize = themeFont.fontSize();
  fontSpacing = themeFont.spacing;
  updateSize();
}
} // namespace katzen
