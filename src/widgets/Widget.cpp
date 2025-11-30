#include "widgets/Widget.hpp"

namespace katzen {
void Widget::resize(Gctx g) {
  m_rect.w = g.clampWidth(padding.getX());
  m_rect.h = g.clampHeight(padding.getY());
}

void Widget::reposition(Vec2 position) {
  m_rect.x = position.x;
  m_rect.y = position.y;
}
} // namespace katzen
