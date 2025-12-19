#include "widgets/Widget.hpp"
#include "bins/Bin.hpp"

namespace katze {
void Widget::resize(Gctx g, FRect &rect) {
  rect.w = g.clampWidth(0);
  rect.h = g.clampHeight(0);
}

void Widget::reposition(FVec2 position, FRect &rect) {
  rect.x = position.x;
  rect.y = position.y;

  if (Bin *bin = dynamic_cast<Bin *>(this); bin != nullptr) {
    bin->repositionChildren(rect);
  }
}
}
