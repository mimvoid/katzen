#ifndef KATZE_WIDGETS_RECTANGLE_HPP
#define KATZE_WIDGETS_RECTANGLE_HPP

#include "Widget.hpp"

namespace katze {
/**
 * Simple rectangle widget.
 */
struct Rectangle : Widget {
  FVec2 maxSize{};

  bool bordered{true};
  bool filled{true};

  Rectangle() = default;

  Rectangle(FVec2 maxSize, bool bordered = true, bool filled = true)
    : maxSize(maxSize), bordered(bordered), filled(filled) {}

  Rectangle(
    float maxWidth, float maxHeight, bool bordered = true, bool filled = true
  )
    : maxSize(maxWidth, maxHeight), bordered(bordered), filled(filled) {}

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_RECTANGLE_HPP
