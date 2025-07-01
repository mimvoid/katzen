#pragma once
#include "Widget.hpp"

namespace katzen {
/**
 * A basic widget with no content.
 *
 * May be useful for specific layouts, but consider box alignments,
 * margins, and padding first.
 */
struct Spacer : Widget {
  using Props = Widget::Props;

  Spacer(unsigned int width, unsigned int height) {
    m_bounds.min.x = width;
    m_bounds.min.y = height;
  }

  Spacer(bool hexpand, bool vexpand) {
    expand.x = hexpand;
    expand.y = vexpand;
  }

  Spacer(Props props) : Widget(props) {}

  void draw([[maybe_unused]] Dctx &d) override {}
};
} // namespace katzen
