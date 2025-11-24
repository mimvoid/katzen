#include "../../include/theme/fonts.hpp"
#include <optional>

namespace katzen::theme {
static std::optional<FontStyle> defaultFontStyle{};

// NOTE: Using value() throws an exception if there is no value, while the
// dereference operators cause undefined behavior.

FontStyle &fontStyle() { return defaultFontStyle.value(); }
Font font() { return defaultFontStyle.value().font; }
float fontSize() { return defaultFontStyle.value().size(); }
float fontSpacing() { return defaultFontStyle.value().spacing; }

void setDefaultFontStyle() { defaultFontStyle.emplace(GetFontDefault()); }
void setFontStyle(FontStyle style) { defaultFontStyle = style; }

void setFontSize(float size) { defaultFontStyle.value().setSize(size); }
void setFontSpacing(float spacing) {
  defaultFontStyle.value().spacing = spacing;
}

void setFontProperties(float size, float spacing) {
  setFontSize(size);
  setFontSpacing(spacing);
}
} // namespace katzen::theme
