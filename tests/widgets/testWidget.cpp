#include <doctest/doctest.h>
#include "widgets/Widget.hpp"

namespace katzen {
// Widget is an abstract class, so create a basic child class for testing
struct Stock : katzen::Widget {
  void draw([[maybe_unused]] katzen::Dctx &d) override {}
};

Gctx g{FontStyle{}};

Gctx &resetGctx() {
  // The tests run without a window open, so fake the window size
  g.w = 960;
  g.h = 640;
  return g;
}

Stock initStock() {
  Stock w = Stock();
  w.resize(resetGctx());
  return w;
}

TEST_CASE("[katzen] Widget Stock position") {
  Stock w = Stock();
  Gctx g = resetGctx();
  w.resize(g);

  const Vec2 pos{w.x(), w.y()};
  SUBCASE("Getting position is consistent") {
    CHECK(pos.x == w.x());
    CHECK(pos.y == w.y());

    const Rect box = w.rect();
    CHECK(pos.x == box.x);
    CHECK(pos.y == box.y);
  }
}
} // namespace katzen
