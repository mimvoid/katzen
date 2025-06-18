#pragma once
#include <raylib.h>
#include <string_view>
#include "../core/Axis.hpp"
#include "../core/vectors.hpp"
#include "../theme/fonts.hpp"

namespace katzen {
struct Text {
  std::string_view content;
  const theme::ThemeFont &font;

  Text(std::string_view content, std::size_t fontId = theme::defaultFontId())
      : content(content), font(theme::getThemeFont(fontId)) {
    updateSize();
  }

  constexpr bool empty() const { return content.empty(); }

  constexpr float size(Axis axis) const {
    switch (axis) {
    case Axis::X: return m_width;
    case Axis::Y: return m_height;
    }
  }

  constexpr float width() const { return m_width; }
  constexpr float height() const { return m_height; }

  constexpr Vec2 measureSize() const {
    if (content.empty()) return {0.0f, 0.0f};

    const Vector2 textSize =
        MeasureTextEx(font.font, content.data(), font.fontSize(), font.spacing);
    return {textSize.x, textSize.y};
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
