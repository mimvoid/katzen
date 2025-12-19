#ifndef KATZE_WIDGETS_RECTANGLE_HPP
#define KATZE_WIDGETS_RECTANGLE_HPP

#include "Widget.hpp"

namespace katze {
/**
 * Simple rectangle widget.
 */
struct Rectangle : Widget {
  FVec2 maxSize{};

  Rectangle(FVec2 maxSize) : maxSize(maxSize) {}
  Rectangle(float maxWidth, float maxHeight) : maxSize(maxWidth, maxHeight) {}

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_RECTANGLE_HPP
