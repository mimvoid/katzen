#ifndef KATZE_BINS_BIN_HPP
#define KATZE_BINS_BIN_HPP

#include <memory>
#include "../core/Vec2.hpp"
#include "../widgets/Widget.hpp"

namespace katze {
/**
 * Manager that positions and resizes child widgets.
 */
struct Bin : Widget {
  virtual void reposition(FVec2 pos, WidgetData &wData) = 0;
};

Bin *dynCastBin(Widget *ptr);
std::shared_ptr<Bin> dynCastBin(std::shared_ptr<Widget> ptr);

void dynReposition(Widget *ptr, FVec2 pos, WidgetData &wData);
void dynReposition(std::shared_ptr<Widget> ptr, FVec2 pos, WidgetData &wData);
} // namespace katze

#endif // !KATZE_BINS_BIN_HPP
