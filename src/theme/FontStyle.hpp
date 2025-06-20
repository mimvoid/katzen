#pragma once
#include <raylib.h>
#include <algorithm>
#include <cassert>

namespace katzen::theme {
struct FontStyle {
  Font font;
  float spacing;

  FontStyle(Font font, float size, float spacing = 0.0f)
      : font(font), spacing(spacing) {
    fontSize(size);
  }

  FontStyle(Font font) : FontStyle(font, font.baseSize) {}

  constexpr float fontSize() const { return m_size; }
  constexpr void fontSize(float size) { m_size = std::max(1.0f, size); }

private:
  float m_size;
};
} // namespace katzen::theme
