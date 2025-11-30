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

void IconLabel::resize(Gctx g) {
  g.pad(padding);
  icon.resize(g);

  if (label.empty()) {
    m_rect.w = icon.width() + padding.getX();
    m_rect.h = icon.height() + padding.getY();
  } else {
    g.w -= icon.width() + spacing;
    label.resize(g);

    m_rect.w = padding.getX() + icon.width() + spacing + label.width();
    m_rect.h = padding.getY() + std::max(icon.height(), label.height());
  }
}

void IconLabel::reposition(Vec2 position) {
  Widget::reposition(position);
  position.x += padding.left;
  position.y += padding.top;

  const float yBound = m_rect.h - padding.getY();

  const float iconYOffset = offset(yBound, icon.height(), Align::CENTER);
  position.y += iconYOffset;
  icon.reposition(position);

  position.x += icon.width() + spacing;
  position.y += offset(yBound, label.height(), Align::CENTER) - iconYOffset;
  label.reposition(position);
}

void IconLabel::draw(Dctx &d) {
  icon.draw(d);
  label.draw(d);
}
} // namespace katzen
