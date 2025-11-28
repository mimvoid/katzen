#pragma once
#include <raylib.h>

namespace katzen {
struct FontStyle {
  Font font{};
  float spacing{0.0f};

  FontStyle() = default;

  FontStyle(Font font, float size, float spacing = 0.0f)
      : font(font), spacing(spacing) {
    setSize(size);
  }

  FontStyle(Font font) : FontStyle(font, font.baseSize) {}

  constexpr float size() const { return m_size; }
  constexpr void setSize(float size) { m_size = (size >= 1.0f) ? size : 1.0f; }

private:
  float m_size{1.0f};
};
} // namespace katzen
