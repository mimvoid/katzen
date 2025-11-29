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

  constexpr Spacer(unsigned int width,
                   unsigned int height,
                   bool hexpand = false,
                   bool vexpand = false) {
    minSize = UVec2{width, height};
    expand = {hexpand, vexpand};
  }

  void draw([[maybe_unused]] Dctx &d) override {}

  struct Builder : WidgetBuilder<Builder> {
    // Create a spacer widget.
    Spacer build() const {
      Spacer spacer(m_minSize.x, m_minSize.y, m_expand.x, m_expand.y);
      spacer.padding = m_padding;
      return spacer;
    }
  };
};
} // namespace katzen
