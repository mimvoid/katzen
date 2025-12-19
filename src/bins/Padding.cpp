#include "bins/Padding.hpp"

namespace katze {
void Padding::resize(Gctx g, FRect &rect) {
  if (child) {
    Gctx gCopy = g;
    gCopy.shrink(pad);
    child->resize(gCopy, childRect);
  } else {
    childRect.w = 0;
    childRect.h = 0;
  }

  rect.w = g.clampWidth(childRect.w + pad.getX());
  rect.h = g.clampHeight(childRect.h + pad.getY());
}

void Padding::repositionChildren(FRect rect) {
  if (child) {
    child->reposition(FVec2{rect.x + pad.left, rect.y + pad.top}, childRect);
  }
}
} // namespace katze
