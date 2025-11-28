#pragma once
#include <raylib.h>
#include "core/Axis.hpp"
#include "core/vectors.hpp"
#include "theme/FontStyle.hpp"

namespace katzen {
struct Text {
  const char *content{""};
  FontStyle &style;

  Text(const char *content, FontStyle &style) : content(content), style(style) {
    updateSize();
  }

  constexpr bool empty() const { return content[0] == '\0'; }

  constexpr float size(Axis axis) const { return m_size.get(axis); }
  constexpr float width() const { return m_size.x; }
  constexpr float height() const { return m_size.y; }

  constexpr Vec2 measureSize() const {
    return (empty()) ? Vec2{}
                     : (Vec2)MeasureTextEx(
                           style.font, content, style.size(), style.spacing);
  }

  constexpr float measureWidth() const { return measureSize().x; }
  constexpr float measureHeight() const { return measureSize().y; }

  constexpr float measureSize(Axis axis) const {
    return measureSize().get(axis);
  }

  constexpr void updateWidth() { m_size.x = measureWidth(); }
  constexpr void updateHeight() { m_size.y = measureHeight(); }

  constexpr void updateSize() {
    updateWidth();
    updateHeight();
  }

  void drawWrapped(Rectangle box, Color color);
  void draw(Vector2 position, Color color);

private:
  Vec2 m_size{0.0f, 0.0f};
};
} // namespace katzen
