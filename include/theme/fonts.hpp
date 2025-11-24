#pragma once
#include "FontStyle.hpp"

namespace katzen::theme {
FontStyle &fontStyle();
Font font();
float fontSize();
float fontSpacing();

void setFontStyle(FontStyle style);
void setDefaultFontStyle();

void setFontProperties(float size, float spacing);
void setFontSize(float size);
void setFontSpacing(float spacing);
} // namespace katzen::theme
