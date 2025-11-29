#pragma once
#include <raylib.h>
#include "core/Rect.hpp"
#include "theme/FontStyle.hpp"

namespace katzen {
/**
 * A graphics context that provides necessary information for resizing widgets.
 */
struct Gctx : Rect {
  FontStyle font{};

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
