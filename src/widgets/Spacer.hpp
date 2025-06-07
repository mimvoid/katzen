#pragma once
#include "Widget.hpp"

namespace katzen::widgets {
struct Spacer : Widget {
  Spacer(unsigned int width, unsigned int height) {
    padding.set(width / 2, height / 2);
  }
};
} // namespace katzen::widgets
