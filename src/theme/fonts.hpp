#pragma once
#include <raylib.h>
#include "FontStyle.hpp"

namespace katzen::theme {
FontStyle loadDefaultFontStyle();
void setFontStyle(FontStyle style);

FontStyle &getFontStyle();
Font getFont();

float getFontSize();
float getFontSpacing();

void setFontProperties(float size, float spacing);
void setFontSize(float size);
void setFontSpacing(float spacing);
} // namespace katzen::theme
