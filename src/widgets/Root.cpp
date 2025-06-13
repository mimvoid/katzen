#include "Root.hpp"

namespace katzen::widgets {
template <typename T>
template <typename... Args>
Root<T>::Root(Args &&...args) : child(args...), m_g(Gctx::init(padding)) {
  repaint();
}

template <typename T>
katzen::Gctx &Root<T>::resetGctx() {
  m_g.reset(padding);

  m_g.x += offset(m_g.w, child.width(), halign);
  m_g.y += offset(m_g.h, child.height(), valign);

  return m_g;
}
} // namespace katzen::widgets
