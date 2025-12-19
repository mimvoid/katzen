#ifndef KATZE_WIDGETS_SPACER_HPP
#define KATZE_WIDGETS_SPACER_HPP

#include "Widget.hpp"

namespace katze {
/**
 * Basic widget with no content. May be useful for specific layouts.
 */
struct Spacer : Widget {
  FVec2 maxSize{};

  void resize(Gctx g, FRect &rect) override;
  void view([[maybe_unused]] Dctx &d, [[maybe_unused]] FRect rect) override {}
};
} // namespace katze

#endif // !KATZE_WIDGETS_SPACER_HPP
