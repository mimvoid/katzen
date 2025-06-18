#include "Label.hpp"

namespace katzen {
Label::Label(std::string_view content,
             bool wrapWords,
             std::size_t fontId,
             std::function<void(Label &)> setup)
    : text(content, fontId), wrapWords(wrapWords) {
  if (setup) setup(*this);
}

float Label::measure(Axis axis) const {
  float size = padding.get(axis);

  if (axis == Axis::X || !willWrap()) {
    size += text.size(axis);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        glm::ceil(text.width() / (maxWidth() - padding.get(Axis::X)));

    size += text.height() * lines;
  }

  return clampSize(size, axis);
}

void Label::repaint(Gctx g) {
  setExternalBounds(g);
  reposition(g);

  text.updateSize();
  resize();
}

void Label::draw(Dctx &d) {
  if (text.empty()) return;

  const Vector2 p{x() + padding.left, y() + padding.top};

  if (willWrap()) {
    text.drawWrapped({p.x,
                      p.y,
                      width() - padding.get(Axis::X),
                      height() - padding.get(Axis::Y)},
                     d.colors.text);
  } else {
    text.draw(p, d.colors.text);
  }
}
} // namespace katzen
