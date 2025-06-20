#include "fonts.hpp"
#include <raylib.h>
#include <optional>

namespace katzen::theme {
static std::optional<FontStyle> defaultFontStyle;

FontStyle loadDefaultFontStyle() {
  assert(!defaultFontStyle.has_value());

  Font fontDefault = GetFontDefault();
  defaultFontStyle.emplace(GetFontDefault(), fontDefault.baseSize);

  return defaultFontStyle.value();
}

void setFontStyle(FontStyle style) { defaultFontStyle = style; }

FontStyle &getFontStyle() { return defaultFontStyle.value(); }
Font getFont() { return defaultFontStyle->font; }

float getFontSize() { return defaultFontStyle->fontSize(); }
float getFontSpacing() { return defaultFontStyle->spacing; }

void setFontProperties(float size, float spacing) {
  defaultFontStyle->fontSize(size);
  defaultFontStyle->spacing = spacing;
}

void setFontSize(float size) { defaultFontStyle->fontSize(size); }
void setFontSpacing(float spacing) { defaultFontStyle->spacing = spacing; }
} // namespace katzen::theme
