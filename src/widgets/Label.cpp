#include "../../include/widgets/Label.hpp"
#include <cmath>

namespace katzen {
float Label::measure(Axis axis) const {
  float size = padding.getSum(axis);

  if (axis == Axis::X || !willWrap()) {
    size += text.size(axis);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        std::ceil(text.width() / (maxWidth() - padding.getSum(Axis::X)));

    size += text.height() * lines;
  }

  return clampSize(size, axis);
}

void Label::repaint(Gctx g) {
  setBounds(g);
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
                      width() - padding.getSum(Axis::X),
                      height() - padding.getSum(Axis::Y)},
                     d.colors.text);
  } else {
    text.draw(p, d.colors.text);
  }
}
} // namespace katzen
