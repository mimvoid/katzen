#include "Label.hpp"
#include <raygui.h>
#include "helpers.hpp"

namespace katzen::widgets {
Label::Label(const Font &font, std::string_view text, float size)
    : font(font),
      text(text),
      wrapWords(true),
      color(GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))),
      fontSize(size),
      fontSpacing(GuiGetStyle(DEFAULT, TEXT_SPACING)) {}

Label::Label(std::function<void(Label &)> setup,
                          const Font &font,
                          std::string_view text,
                          float size)
    : Label(font, text, size) {
  setup(*this);
}

Label::Label(const Font &font, std::string_view text) : Label(font, text, 24) {}

float Label::measureSize(Axis axis) const {
  float labelSize = padding.get(axis);

  if (axis == Axis::X || !willWrap()) {
    labelSize += textSize(axis);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        glm::ceil(textWidth() / (maxWidth() - padding.get(Axis::X)));
    labelSize += textSize(axis) * lines;
  }

  return glm::clamp(labelSize, (float)minSize(axis), (float)maxSize(axis));
}

void Label::draw(glm::vec2 p) {
  if (text.empty()) return;

  p.x += padding.left;
  p.y += padding.top;

  if (willWrap()) {
    DrawTextBoxed(font,
                  text.data(),
                  {p.x,
                   p.y,
                   width() - padding.get(Axis::X),
                   height() - padding.get(Axis::Y)},
                  fontSize,
                  fontSpacing,
                  color);
  } else {
    DrawTextEx(font, text.data(), {p.x, p.y}, fontSize, fontSpacing, color);
  }
}
} // namespace katzen::widgets
