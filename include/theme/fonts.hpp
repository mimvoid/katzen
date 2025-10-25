#pragma once
#include <raylib.h>
#include "FontStyle.hpp"

namespace katzen::theme {
FontStyle loadDefaultFontStyle();
FontStyle &fontStyle();
void setFontStyle(FontStyle style);

Font font();

float fontSize();
float fontSpacing();

void setFontProperties(float size, float spacing);
void setFontSize(float size);
void setFontSpacing(float spacing);
} // namespace katzen::theme
