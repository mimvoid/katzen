#pragma once
#include <raylib.h>
#include "../core/Axis.hpp"
#include "../core/vectors.hpp"
#include "../theme/FontStyle.hpp"

namespace katzen {
struct Text {
  const char *content;
  theme::FontStyle &style;

  Text(const char *content, theme::FontStyle &style)
      : content(content), style(style) {
    updateSize();
  }

  constexpr bool empty() const { return content[0] == '\0'; }

  constexpr float size(Axis axis) const {
    switch (axis) {
    case Axis::X: return m_width;
    case Axis::Y: return m_height;
    }
  }

  constexpr float width() const { return m_width; }
  constexpr float height() const { return m_height; }

  constexpr Vec2 measureSize() const {
    if (empty()) return {0.0f, 0.0f};
    return MeasureTextEx(
        style.font, content, style.size(), style.spacing);
  }

  constexpr float measureWidth() const { return measureSize().x; }
  constexpr float measureHeight() const { return measureSize().y; }

  constexpr float measureSize(Axis axis) const {
    switch (axis) {
    case Axis::X: return measureWidth();
    case Axis::Y: return measureHeight();
    }
  }

  constexpr void updateWidth() { m_width = measureWidth(); }
  constexpr void updateHeight() { m_height = measureHeight(); }

  constexpr void updateSize() {
    updateWidth();
    updateHeight();
  }

  void drawWrapped(Rectangle box, Color color);
  void draw(Vector2 position, Color color);

private:
  float m_width;
  float m_height;
};
} // namespace katzen
