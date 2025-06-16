#include "IconLabel.hpp"
#include <raylib.h>

namespace katzen {
IconLabel::IconLabel(uint8_t iconId,
                     std::string_view text,
                     std::size_t fontIndex,
                     std::function<void(IconLabel &)> setup)
    : icon(iconId), label(text, fontIndex) {
  if (setup) setup(*this);
}

float IconLabel::measureSize(Axis axis) const {
  float size = padding.get(axis);

  switch (axis) {
  case Axis::Y: size += glm::max(icon.height(), label.height()); break;
  case Axis::X:
    size += icon.width() + label.width();
    if (!icon.empty() && !label.text.empty()) {
      size += spacing;
    }
    break;
  }

  return clampSize(size, axis);
}

void IconLabel::repaint(Gctx g) {
  Gctx gIcon = g;
  gIcon.pad(padding);
  Gctx gLabel = gIcon;

  icon.setExternalBounds(g);
  icon.updateSize();

  gLabel.translateClip(Axis::X,
                       (icon.empty() || label.text.empty())
                           ? icon.width()
                           : icon.width() + spacing);

  label.setExternalBounds(g);
  label.updateSize();

  Widget::repaint(g);

  if (!icon.empty() && !label.text.empty()) {
    const float iconHeight = icon.height();
    const float labelHeight = label.height();

    if (iconHeight > labelHeight) {
      gLabel.translateY((iconHeight - labelHeight) / 2.0f);
    } else if (iconHeight < labelHeight) {
      gIcon.translateY((labelHeight - iconHeight) / 2.0f);
    }
  }

  icon.position(gIcon);
  label.position(gLabel);
}

void IconLabel::draw(Dctx &d) {
  icon.draw(d);
  label.draw(d);
}
} // namespace katzen
