#include "Label.hpp"
#include "helpers.hpp"

namespace katzen {
Label::Label(const Font &font,
             std::string_view content,
             float size,
             bool wrapWords,
             std::function<void(Label &)> setup)
    : text(font, content, size), wrapWords(wrapWords) {
  if (setup) setup(*this);
}

Label::Label(std::string_view content,
             bool wrapWords,
             std::size_t fontIndex,
             std::function<void(Label &)> setup)
    : text(content, fontIndex), wrapWords(wrapWords) {
  if (setup) setup(*this);
}

float Label::measureSize(Axis axis) const {
  float labelSize = padding.get(axis);

  if (axis == Axis::X || !willWrap()) {
    labelSize += text.size(axis);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        glm::ceil(text.width() / (maxWidth() - padding.get(Axis::X)));

    if (lines != 0) {
      labelSize += text.height() * lines;
    }
  }

  return glm::clamp(labelSize, (float)minSize(axis), (float)maxSize(axis));
}

void Label::repaint(Gctx g) {
  externalBounds.x = g.w;
  externalBounds.y = g.h;

  position(g);

  text.updateSize();
  updateSize();
}

void Label::draw(glm::vec2 p) {
  if (text.empty()) return;

  p.x += padding.left;
  p.y += padding.top;

  if (willWrap()) {
    drawTextBoxed(text.font,
                  text.content.data(),
                  {p.x,
                   p.y,
                   width() - padding.get(Axis::X),
                   height() - padding.get(Axis::Y)},
                  text.fontSize(),
                  text.fontSpacing,
                  text.color);
  } else {
    DrawTextEx(text.font,
               text.content.data(),
               {p.x, p.y},
               text.fontSize(),
               text.fontSpacing,
               text.color);
  }
}
} // namespace katzen
