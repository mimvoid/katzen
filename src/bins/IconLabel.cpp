#include "bins/IconLabel.hpp"
#include "core/Align.hpp"

namespace katze {
void IconLabel::resize(Gctx g, FRect &rect) {
  icon.resize(g, iconRect);

  if (label.empty()) {
    labelRect.w = 0;
    labelRect.h = 0;

    rect.w = iconRect.w;
    rect.h = iconRect.h;
  } else {
    g.w -= iconRect.w + spacing;
    label.resize(g, labelRect);

    rect.w = iconRect.w + spacing + labelRect.w;
    rect.h = std::max(iconRect.h, labelRect.h);
  }
}

void IconLabel::repositionChildren(FRect rect) {
  FVec2 position{rect.x, rect.y};

  const float iconYOffset = offset(rect.h, iconRect.h, Align::CENTER);
  position.y += iconYOffset;
  icon.reposition(position, iconRect);

  position.x += iconRect.w + spacing;
  position.y += offset(rect.h, labelRect.h, Align::CENTER) - iconYOffset;
  label.reposition(position, labelRect);
}

void IconLabel::view(Dctx &d, [[maybe_unused]] FRect rect) {
  icon.view(d, iconRect);
  label.view(d, labelRect);
}
} // namespace katze
