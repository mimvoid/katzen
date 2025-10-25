#include "../../include/parts/Text.hpp"
#include "../../include/parts/textHelpers.hpp"

namespace katzen {
void Text::draw(Vector2 position, Color color) {
  DrawTextEx(style.font, content, position, style.size(), style.spacing, color);
}

void Text::drawWrapped(Rectangle box, Color color) {
  drawTextBoxed(style.font, content, box, style.size(), style.spacing, color);
}
} // namespace katzen
