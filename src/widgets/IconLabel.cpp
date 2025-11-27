#include "widgets/IconLabel.hpp"
#include <algorithm>
#include <cassert>
#include <utility>

namespace katzen {
IconLabel IconLabel::Builder::build() const {
  assert(m_label && m_icon
         && "Please provide children for the katzen IconLabel!");

  IconLabel il{std::move(*m_icon), std::move(*m_label), m_spacing};
  il.valign = m_valign;
  return il;
}

IconLabel::IconLabel(Icon &&icon, Label &&label, int spacing, Align valign)
    : spacing(spacing),
      valign(valign),
      icon(std::move(icon)),
      label(std::move(label)) {}

float IconLabel::measure(Axis axis) const {
  float size = padding.getSum(axis);

  if (axis == Axis::X) {
    size += icon.width();
    if (!label.text.empty()) {
      size += spacing + label.width();
    }
  } else {
    size = std::max(icon.height(), label.height());
  }

  return clampSize(size, axis);
}

void IconLabel::repaint(Gctx g) {
  Widget::repaint(g);
  g.pad(padding);

  const float paddedHeight = m_rect.h - padding.getSum(Axis::Y);
  const float iconOffset = offset(paddedHeight, icon.height(), valign);

  g.translateClip(0.0f, iconOffset);
  icon.repaint(g);

  if (!label.text.empty()) {
    g.translateClip(icon.width() + spacing,
                    offset(paddedHeight, label.height(), valign) - iconOffset);
    label.repaint(g);
  }
}

void IconLabel::draw(Dctx &d) {
  icon.draw(d);
  label.draw(d);
}
} // namespace katzen
