#pragma once
#include <raylib.h>
#include "core/vectors.hpp"

namespace katzen {
/**
 * Stores a raylib Font and information about how to size and draw it.
 *
 * It does not unload the stored font on destruction, so make sure to have
 * a system in place to unload and free the font when it's no longer needed.
 */
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

  constexpr Vec2 measure(const char *content) const {
    if (!content || content[0] == '\0') return Vec2{0, 0};
    return (Vec2)MeasureTextEx(font, content, m_size, spacing);
  }

private:
  float m_size{1.0f};
};
} // namespace katzen
