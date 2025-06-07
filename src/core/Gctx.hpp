#pragma once
#include "Rect.hpp"
#include <raylib.h>

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

  constexpr void reset(Edges padding) {
    reset();
    pad(padding);
  }
};
} // namespace katzen
