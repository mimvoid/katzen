#pragma once
#include <raylib.h>
#include "Rect.hpp"

namespace katzen {
struct Gctx : Rect {
  static Gctx init() {
    Gctx g{};
    g.reset();
    return g;
  }

  static Gctx init(Edges padding) {
    Gctx g{};
    g.reset(padding);
    return g;
  }

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
