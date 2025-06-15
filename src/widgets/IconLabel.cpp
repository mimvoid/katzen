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

  return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
}

void IconLabel::repaint(Gctx g) {
  Gctx gIcon = g;
  gIcon.pad(padding);
  Gctx gLabel = gIcon;

  icon.externalBounds.x = g.w;
  icon.externalBounds.y = g.h;

  icon.updateWidth();
  gLabel.translateClip(Axis::X,
                       (icon.empty() || label.text.empty())
                           ? icon.width()
                           : icon.width() + spacing);

  label.externalBounds.x = gLabel.w;
  label.externalBounds.y = gLabel.h;

  icon.updateHeight();
  label.updateWidth();
  label.updateHeight();

  Widget::repaint(g);

  if (!icon.empty() && !label.text.empty()) {
    const float iconHeight = icon.height();
    const float labelHeight = label.height();

    if (iconHeight > labelHeight) {
      gLabel.translate(Axis::Y, (iconHeight - labelHeight) / 2.0f);
    } else if (labelHeight > iconHeight) {
      gIcon.translate(Axis::Y, (labelHeight - iconHeight) / 2.0f);
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
