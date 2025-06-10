#pragma once
#include "Widget.hpp"

namespace katzen::widgets {
/**
 * A basic widget with no content.
 *
 * May be useful for specific layouts, but consider box alignments,
 * margins, and padding first.
 */
struct Spacer : Widget {
  Spacer(unsigned int width, unsigned int height) {
    bounds.min.x = width;
    bounds.min.y = height;
  }

  Spacer(bool hexpand, bool vexpand) {
    expand.x = hexpand;
    expand.y = vexpand;
  }
};
} // namespace katzen::widgets
