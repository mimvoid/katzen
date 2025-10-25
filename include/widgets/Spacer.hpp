#pragma once
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A basic widget with no content. May be useful for specific layouts.
 */
struct Spacer : Widget {
  struct Builder : WidgetBuilder {
    constexpr Builder() = default;

    // Create a spacer widget.
    Spacer build() const {
      Spacer spacer{m_minSize.x, m_minSize.y, m_expand.x, m_expand.y};
      spacer.padding = m_padding;
      return spacer;
    }
  };

  constexpr Spacer() = default;

  constexpr Spacer(unsigned int width,
                   unsigned int height,
                   bool hexpand = false,
                   bool vexpand = false) {
    minSize.x = width;
    minSize.y = height;
    expand.x = hexpand;
    expand.y = vexpand;
  }

  void draw([[maybe_unused]] Dctx &d) override {}
};
} // namespace katzen
