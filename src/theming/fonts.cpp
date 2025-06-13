#include "fonts.hpp"
#include <glm/ext/scalar_common.hpp>
#include <vector>

namespace katzen::theme {
struct ThemeFont {
  Font font;
  float size;
  float spacing = 0.0f;

  ThemeFont(const Font &that) : size(that.baseSize) {
    font.baseSize = that.baseSize;
    font.glyphCount = that.glyphCount;
    font.texture = that.texture;

    std::copy(that.recs, that.recs + that.glyphCount, font.recs);
    std::copy(that.glyphs, that.glyphs + that.glyphCount, font.glyphs);
  }

  ~ThemeFont() { UnloadFont(font); }
};

std::vector<ThemeFont> fonts;

std::size_t loadFont(std::string_view filePath) {
  fonts.emplace_back(LoadFont(filePath.data()));
  return fonts.size() - 1;
}

std::size_t loadFont(std::string_view filePath, float fontSize) {
  fonts.emplace_back(LoadFontEx(filePath.data(), fontSize, 0, 0));
  return fonts.size() - 1;
}

void setFontSize(std::size_t fontIndex, float size) {
  if (fontIndex >= fonts.size()) {
    return;
  }
  fonts.at(fontIndex).size = glm::max(1.0f, size);
}

void setFontSpacing(std::size_t fontIndex, float spacing) {
  if (fontIndex >= fonts.size()) {
    return;
  }
  fonts.at(fontIndex).spacing = spacing;
}
} // namespace katzen::theme
