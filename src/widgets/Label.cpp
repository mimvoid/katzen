#include "Label.hpp"
#include "../components/textHelpers.hpp"

namespace katzen {
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

void Label::draw(Dctx &d) {
  if (text.empty()) return;

  const Vector2 p{x() + padding.left, y() + padding.top};

  if (willWrap()) {
    drawTextBoxed(text.font.font,
                  text.content.data(),
                  {p.x,
                   p.y,
                   width() - padding.get(Axis::X),
                   height() - padding.get(Axis::Y)},
                  text.font.fontSize(),
                  text.font.spacing,
                  d.colors.text);
  } else {
    DrawTextEx(text.font.font,
               text.content.data(),
               p,
               text.font.fontSize(),
               text.font.spacing,
               d.colors.text);
  }
}
} // namespace katzen
