#pragma once
#include <raylib.h>
#include <cstddef>
#include <string_view>
#include "ThemeFont.hpp"

namespace katzen::theme {
std::size_t loadFont(Font &&font);
std::size_t loadFont(std::string_view filePath);
std::size_t loadFont(std::string_view filePath,
                     float preferredSize,
                     int codepointCount = 0);

std::size_t defaultFontId();
void setDefaultFont(std::size_t fontId);

const ThemeFont &getThemeFont(std::size_t fontId = defaultFontId());
const Font &getFont(std::size_t fontId = defaultFontId());
float getFontSize(std::size_t fontId = defaultFontId());
float getFontSpacing(std::size_t fontId = defaultFontId());

void setFontProperties(float size, float spacing, std::size_t fontId = defaultFontId());
void setFontSize(float size, std::size_t fontId = defaultFontId());
void setFontSpacing(float spacing, std::size_t fontId = defaultFontId());
} // namespace katzen::theme
