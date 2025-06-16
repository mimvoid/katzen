#include "Text.hpp"
#include "textHelpers.hpp"

namespace katzen {
void Text::draw(Vector2 position, Color color) {
  DrawTextEx(font.font,
             content.data(),
             position,
             font.fontSize(),
             font.spacing,
             color);
}

void Text::drawWrapped(Rectangle box, Color color) {
  drawTextBoxed(
      font.font, content.data(), box, font.fontSize(), font.spacing, color);
}
} // namespace katzen
