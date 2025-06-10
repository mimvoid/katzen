#include "IconLabel.hpp"
#include <raylib.h>

namespace katzen::widgets {
IconLabel::IconLabel(int iconId, const Font &font, std::string_view text)
    : icon(iconId), label(font, text) {}

IconLabel::IconLabel(int iconId,
                     const Font &font,
                     std::string_view text,
                     float size)
    : icon(iconId), label(font, text, size) {}

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

void IconLabel::draw(glm::vec2 p) {
  p.x -= x();
  p.y -= y();

  if (!icon.empty()) {
    icon.draw({p.x + icon.x(), p.y + icon.y()});
  }
  if (!label.text.empty()) {
    label.draw({p.x + label.x(), p.y + label.y()});
  }
}
} // namespace katzen::widgets
