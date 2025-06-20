#include "Text.hpp"
#include "textHelpers.hpp"

namespace katzen {
void Text::draw(Vector2 position, Color color) {
  DrawTextEx(style.font,
             content.data(),
             position,
             style.fontSize(),
             style.spacing,
             color);
}

void Text::drawWrapped(Rectangle box, Color color) {
  drawTextBoxed(
      style.font, content.data(), box, style.fontSize(), style.spacing, color);
}
} // namespace katzen
