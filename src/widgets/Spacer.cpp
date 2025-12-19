#include "widgets/Spacer.hpp"

namespace katze {
void Spacer::resize(Gctx g, FRect &rect) {
  rect.w = g.clampWidth(maxSize.x);
  rect.h = g.clampHeight(maxSize.y);
}
}
