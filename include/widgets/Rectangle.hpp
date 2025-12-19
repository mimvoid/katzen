#ifndef KATZE_WIDGETS_RECTANGLE_HPP
#define KATZE_WIDGETS_RECTANGLE_HPP

#include "Widget.hpp"

namespace katze {
/**
 * Simple rectangle widget.
 */
struct Rectangle : Widget {
  FVec2 maxSize{};
  bool filled{false};

  Rectangle() = default;

  Rectangle(FVec2 maxSize, bool filled = false)
    : maxSize(maxSize), filled(filled) {}

  Rectangle(float maxWidth, float maxHeight, bool filled = false)
    : maxSize(maxWidth, maxHeight), filled(filled) {}

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_RECTANGLE_HPP
