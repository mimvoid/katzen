#pragma once
#include <functional>
#include <string_view>
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that displays text.
 */
struct Label : Widget {
  const Font &font;
  std::string_view text;
  bool wrapWords;
  Color color;

  Label(const Font &font, std::string_view text);
  Label(const Font &font, std::string_view text, float size);
  Label(std::function<void(Label &)> setup,
        const Font &font,
        std::string_view text,
        float size);

  constexpr float textSize(Axis axis) const {
    if (text.empty()) return 0;

    const Vector2 textSize =
        MeasureTextEx(font, text.data(), m_fontSize, m_fontSpacing);

    return axis == Axis::X ? textSize.x : textSize.y;
  }

  constexpr float textWidth() const { return textSize(Axis::X); }
  constexpr float textHeight() const { return textSize(Axis::Y); }

  constexpr bool willWrap() const {
    return wrapWords && (textWidth() + padding.get(Axis::X) > maxWidth());
  }

  void draw(glm::vec2 p) override;

protected:
  float m_fontSize;
  int m_fontSpacing;

  float measureSize(Axis axis) const override;
};
} // namespace katzen::widgets
