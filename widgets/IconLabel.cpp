#include "../widgets.hpp"
#include <algorithm>
#include <raylib.h>

IconLabel::IconLabel(GuiIconName icon, const Font &font, const char *text)
    : icon(icon), label(font, text) {
  label.wrapWords = false;
}
IconLabel::IconLabel(GuiIconName icon,
                     const Font &font,
                     const char *text,
                     float size)
    : icon(icon), label(font, text, size) {
  label.wrapWords = false;
}

float IconLabel::measureSize(Axis a) const {
  float size = getTotalPadding(a);

  switch (a) {
    case Axis::Y:
      size += std::max(icon.getHeight(), label.getHeight());
      break;
    case Axis::X:
      size += icon.getWidth() + label.getWidth();
      if (!icon.isEmpty() && !label.isEmpty()) {
        size += spacing;
      }
      break;
  }

  return std::clamp(size, (float)getMinSize(a), (float)getMaxSize(a));
}

void IconLabel::repaint(Gctx g) {
  Gctx gIcon = g;
  pad(gIcon);
  Gctx gLabel = gIcon;

  icon.setExternalBounds(gIcon.bounds);

  icon.updateWidth();
  TranslateClipGctx(gLabel,
                    Axis::X,
                    (icon.isEmpty() || label.isEmpty())
                        ? icon.getWidth()
                        : icon.getWidth() + spacing);
  label.setExternalBounds(gLabel.bounds);

  icon.updateHeight();
  label.updateWidth();
  label.updateHeight();

  Widget::repaint(g);

  if (!icon.isEmpty() && !label.isEmpty()) {
    const float iconHeight = icon.getHeight();
    const float labelHeight = label.getHeight();

    if (iconHeight > labelHeight) {
      TranslateGctx(gLabel, Axis::Y, (iconHeight - labelHeight) / 2.0f);
    } else if (labelHeight > iconHeight) {
      TranslateGctx(gIcon, Axis::Y, (labelHeight - iconHeight) / 2.0f);
    }
  }

  icon.setPosition(gIcon.p);
  label.setPosition(gLabel.p);
}

void IconLabel::draw(Vector2 p) {
  p.x -= getX();
  p.y -= getY();

  if (!icon.isEmpty()) {
    icon.draw({p.x + icon.getX(), p.y + icon.getY()});
  }
  if (!label.isEmpty()) {
    label.draw({p.x + label.getX(), p.y + label.getY()});
  }
}
