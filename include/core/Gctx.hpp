#pragma once
#include <raylib.h>
#include "Rect.hpp"

namespace katzen {
struct Gctx : Rect {
  Gctx() { reset(); }
  Gctx(Edges padding) { reset(padding); }

  void reset() {
    x = 0;
    y = 0;
    w = GetRenderWidth();
    h = GetRenderHeight();
  }

  void reset(Edges padding) {
    reset();
    pad(padding);
  }
};
} // namespace katzen
