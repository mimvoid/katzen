#include "bins/Bin.hpp"
#include <memory>

namespace katze {
Bin *dynCastBin(Widget *ptr) { return dynamic_cast<Bin *>(ptr); }

std::shared_ptr<Bin> dynCastBin(std::shared_ptr<Widget> ptr) {
  return std::dynamic_pointer_cast<Bin, Widget>(ptr);
}

void dynReposition(Widget *ptr, FVec2 pos, WidgetData &wData) {
  if (ptr == nullptr) return;

  if (Bin *bin = dynCastBin(ptr); bin != nullptr) {
    bin->reposition(pos, wData);
  } else {
    wData.rect.x = pos.x;
    wData.rect.y = pos.y;
  }
}

void dynReposition(std::shared_ptr<Widget> ptr, FVec2 pos, WidgetData &wData) {
  if (ptr == nullptr) return;

  if (std::shared_ptr<Bin> bin = dynCastBin(ptr); bin != nullptr) {
    bin->reposition(pos, wData);
  } else {
    wData.rect.x = pos.x;
    wData.rect.y = pos.y;
  }
}
} // namespace katze
