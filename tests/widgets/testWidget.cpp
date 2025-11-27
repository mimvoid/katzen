#include <doctest/doctest.h>
#include "widgets/Widget.hpp"

namespace katzen {
// Widget is an abstract class, so create a basic child class for testing
struct Stock : katzen::Widget {
  void draw([[maybe_unused]] katzen::Dctx &d) override {}
};

Gctx debugGctx() {
  // The tests run without a window open, so fake the window size
  Gctx g{};
  g.x = 0;
  g.y = 0;
  g.w = 960;
  g.h = 640;
  return g;
}

Stock initStock() {
  Stock w = Stock();
  w.repaint(debugGctx());
  return w;
}

TEST_CASE("[katzen] Widget Stock position") {
  Stock w = Stock();
  const Gctx g = debugGctx();
  w.repaint(g);

  const Vec2 pos{w.x(), w.y()};
  SUBCASE("Getting position is consistent") {
    CHECK(pos.x == w.x());
    CHECK(pos.y == w.y());

    const Rect box = w.rect();
    CHECK(pos.x == box.x);
    CHECK(pos.y == box.y);
  }

  SUBCASE("Position is consistent with Gctx") {
    CHECK(pos.x == g.x);
    CHECK(pos.y == g.y);
  }
}

TEST_CASE("[katzen] Widget Stock max size") {
  Stock w = Stock();
  const Gctx g = debugGctx();
  w.repaint(g);

  SUBCASE("Maximum size is consistent with Gctx bounds") {
    CHECK(w.maxWidth() == g.w);
    CHECK(w.maxHeight() == g.h);
  }
}

TEST_CASE("[katzen] Widget Stock min size") {
  Stock w = Stock();
  const Gctx g = debugGctx();
  w.repaint(g);

  SUBCASE("Set minimum size to greater than Gctx bounds") {
    const unsigned int minWidth = g.w + 15.0f;
    const unsigned int minHeight = g.h + 20.0f;

    w.minSize.x = minWidth;
    w.minSize.y = minHeight;
    w.repaint(g);

    CHECK(w.maxWidth() == g.w);
    CHECK(w.maxHeight() == g.h);
  }
}
} // namespace katzen
