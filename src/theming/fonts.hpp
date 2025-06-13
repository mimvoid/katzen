#pragma once
#include <cstddef>
#include <string_view>
#include <raylib.h>

namespace katzen::theme {
std::size_t loadFont(std::string_view filePath);
std::size_t loadFont(std::string_view filePath, float fontSize);

void setFontSize(std::size_t fontIndex, float size);
void setFontSpacing(std::size_t fontIndex, float spacing);
}
