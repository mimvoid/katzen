#pragma once
#include <raylib.h>
#include <glm/ext/scalar_common.hpp>

namespace katzen::theme {
struct ThemeFont {
  Font font;
  float spacing = 0.0f;

  ThemeFont(const Font &that)
      : font{that.baseSize,
             that.glyphCount,
             that.glyphPadding,
             that.texture,
             nullptr,
             nullptr},
        m_size(that.baseSize) {
    std::copy(that.recs, that.recs + that.glyphCount, font.recs);
    std::copy(that.glyphs, that.glyphs + that.glyphCount, font.glyphs);
  }

  ThemeFont(Font &&that) : font(that), m_size(that.baseSize) {
    that.glyphCount = 0;
    that.recs = nullptr;
    that.glyphs = nullptr;
  }

  ~ThemeFont() { UnloadFont(font); }

  constexpr float fontSize() const { return m_size; }
  constexpr void fontSize(float size) { m_size = glm::max(1.0f, size); }

private:
  float m_size;
};
} // namespace katzen::theme
