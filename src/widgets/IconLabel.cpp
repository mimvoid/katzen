#include "IconLabel.hpp"
#include <raylib.h>

namespace katzen {
IconLabel::IconLabel(uint8_t iconId,
                     std::string_view text,
                     theme::FontStyle &style,
                     std::function<void(IconLabel &)> setup)
    : spacing(style.fontSize() / 4), icon(iconId), label(text, style) {
  if (setup) setup(*this);
}

float IconLabel::measure(Axis axis) const {
  float size = padding.get(axis);

  switch (axis) {
  case Axis::Y: size += std::max(icon.height(), label.height()); break;
  case Axis::X: size += icon.width() + spacing + label.width(); break;
  }

  return clampSize(size, axis);
}

void IconLabel::repaint(Gctx g) {
  Gctx gIcon = g;
  gIcon.pad(padding);
  Gctx gLabel = gIcon;

  icon.setExternalBounds(g);
  icon.resize();

  gLabel.translateClip(Axis::X, icon.width() + spacing);

  label.setExternalBounds(g);
  label.resize();

  Widget::repaint(g);

  const float iconHeight = icon.height();
  const float labelHeight = label.height();

  if (iconHeight > labelHeight) {
    gLabel.translateY((iconHeight - labelHeight) / 2.0f);
  } else if (iconHeight < labelHeight) {
    gIcon.translateY((labelHeight - iconHeight) / 2.0f);
  }

  icon.reposition(gIcon);
  label.reposition(gLabel);
}

void IconLabel::draw(Dctx &d) {
  icon.draw(d);
  label.draw(d);
}
} // namespace katzen
