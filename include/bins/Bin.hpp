#ifndef KATZE_BINS_BIN_HPP
#define KATZE_BINS_BIN_HPP

#include <memory>
#include "../widgets/Widget.hpp"

namespace katze {
/**
 * Manager that positions and resizes child widgets.
 */
struct Bin : Widget {
  virtual void repositionChildren(FRect rect) = 0;
};

Bin *dynCastBin(Widget *ptr);
std::shared_ptr<Bin> dynCastBin(std::shared_ptr<Widget> ptr);
} // namespace katze

#endif // !KATZE_BINS_BIN_HPP
