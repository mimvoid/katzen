#pragma once
#include <raylib.h>
#include <glm/ext/vector_float2.hpp>
#include <string_view>
#include "../core/Axis.hpp"

namespace katzen {
struct Text {
  std::string_view text;
  const Font &font;
  float fontSize;
  float fontSpacing;
  Color color;

  Text(const Font &font, std::string_view text);
  Text(const Font &font, std::string_view text, float size);

  constexpr glm::vec2 size() const {
    if (text.empty()) return {0.0f, 0.0f};

    const Vector2 textSize =
        MeasureTextEx(font, text.data(), fontSize, fontSpacing);
    return {textSize.x, textSize.y};
  }

  constexpr float size(Axis axis) const {
    switch (axis) {
      case Axis::X:
        return size().x;
      case Axis::Y:
        return size().y;
    }
  }

  constexpr float width() const { return size().x; }
  constexpr float height() const { return size().y; }
};
} // namespace katzen
