#include "../../include/theme/fonts.hpp"
#include <raylib.h>
#include <cassert>
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

FontStyle &fontStyle() { return defaultFontStyle.value(); }
Font font() { return defaultFontStyle->font; }

float fontSize() { return defaultFontStyle->size(); }
float fontSpacing() { return defaultFontStyle->spacing; }

void setFontProperties(float size, float spacing) {
  setFontSize(size);
  setFontSpacing(spacing);
}
void setFontSize(float size) { defaultFontStyle->setSize(size); }
void setFontSpacing(float spacing) { defaultFontStyle->spacing = spacing; }
} // namespace katzen::theme
