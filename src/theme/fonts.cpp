#include "fonts.hpp"
#include <iterator>
#include <memory>
#include <vector>

namespace katzen::theme {
static std::size_t m_defaultFontId;

// It seems the allocator cannot work with ThemeFont, so I used unique pointers
// for now. It's likely something to do with how raylib's Font uses pointers for
// its Rectangles and GlyphInfo
static std::vector<std::unique_ptr<ThemeFont>> fonts{};

std::size_t loadFont(Font &&font) {
  auto iter =
      fonts.emplace(fonts.cend(), std::make_unique<ThemeFont>(std::move(font)));
  return std::distance(fonts.begin(), iter);
}

std::size_t loadFont(std::string_view filePath) {
  auto iter = fonts.emplace(
      fonts.cend(), std::make_unique<ThemeFont>(LoadFont(filePath.data())));
  return std::distance(fonts.begin(), iter);
}

std::size_t
loadFont(std::string_view filePath, float preferredSize, int codepointCount) {
  auto iter =
      fonts.emplace(fonts.cend(),
                    std::make_unique<ThemeFont>(LoadFontEx(
                        filePath.data(), preferredSize, 0, codepointCount)));
  return std::distance(fonts.begin(), iter);
}

const ThemeFont &getThemeFont(std::size_t fontId) {
  return *fonts.at(fontId).get();
}

const Font &getFont(std::size_t fontId) { return fonts.at(fontId)->font; }

float getFontSize(std::size_t fontId) { return fonts.at(fontId)->fontSize(); }

float getFontSpacing(std::size_t fontId) { return fonts.at(fontId)->spacing; }

std::size_t defaultFontId() { return m_defaultFontId; }
const ThemeFont &getDefaultFont() { return *fonts.at(m_defaultFontId); }

void setDefaultFont(std::size_t fontId) {
  if (fontId >= fonts.size()) return;
  m_defaultFontId = fontId;
}

void setFontProperties(float size, float spacing, std::size_t fontId) {
  const std::unique_ptr<ThemeFont> &targetFont = fonts.at(fontId);
  targetFont->fontSize(size);
  targetFont->spacing = spacing;
}

void setFontSize(float size, std::size_t fontId) {
  fonts.at(fontId)->fontSize(size);
}

void setFontSpacing(float spacing, std::size_t fontId) {
  fonts.at(fontId)->spacing = spacing;
}
} // namespace katzen::theme
