#pragma once
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A basic widget with no content. May be useful for specific layouts.
 */
struct Spacer : Widget {
  struct Builder;

  constexpr Spacer() = default;

  constexpr Spacer(
    int leftPad, int topPad, bool hexpand = false, bool vexpand = false
  )
    : Widget({topPad, 0, 0, leftPad}, {hexpand, vexpand}) {}

  void draw([[maybe_unused]] Dctx &d) override {}

  struct Builder : WidgetBuilder<Builder> {
    // Create a spacer widget.
    Spacer build() const {
      Spacer spacer(m_padding.left, m_padding.top, m_expand.x, m_expand.y);
      spacer.padding.bottom = m_padding.bottom;
      spacer.padding.right = m_padding.right;
      return spacer;
    }
  };
};
} // namespace katzen
