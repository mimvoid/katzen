#include "bins/Capsule.hpp"

namespace katze {
void Capsule::resize(Gctx g, FRect &rect) {
  if (child) {
    child->resize(g, childRect);
  } else {
    childRect.w = 0;
    childRect.h = 0;
  }

  rect.w = childRect.w;
  rect.h = childRect.h;
}

void Capsule::repositionChildren(FRect rect) {
  if (child) {
    child->reposition(FVec2{rect.x, rect.y}, childRect);
  }
}

void Capsule::view(Dctx &d, [[maybe_unused]] FRect rect) {
  if (child) {
    child->view(d, childRect);
  }
}
}
