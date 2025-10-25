#include "../../include/widgets/Widget.hpp"
#include <catch2/catch_test_macros.hpp>

using katzen::Vec2;
using katzen::Edges;
using katzen::Gctx;
using katzen::Rect;

// Widget is an abstract class, so create a basic child class for testing
struct Stock : katzen::Widget {
  void draw([[maybe_unused]] katzen::Dctx &d) override {}
};

Gctx DebugGctx() {
  // The tests run without a window open, so fake the window size
  Gctx g{};
  g.x = 0;
  g.y = 0;
  g.w = 960;
  g.h = 640;
  return g;
}

Stock InitStock() {
  Stock w = Stock();
  w.repaint(DebugGctx());
  return w;
}

TEST_CASE("Stock position", "[widget]") {
  Stock w = Stock();
  const Gctx g = DebugGctx();
  w.repaint(g);

  const Vec2 pos{w.x(), w.y()};
  SECTION("Getting position is consistent") {
    REQUIRE(pos.x == w.x());
    REQUIRE(pos.y == w.y());

    const Rect box = w.rect();
    REQUIRE(pos.x == box.x);
    REQUIRE(pos.y == box.y);
  }

  SECTION("Position is consistent with Gctx") {
    REQUIRE(pos.x == g.x);
    REQUIRE(pos.y == g.y);
  }
}

TEST_CASE("No widget padding by default", "[widget]") {
  const Edges padding = InitStock().padding;
  REQUIRE(padding.top == 0);
  REQUIRE(padding.right == 0);
  REQUIRE(padding.bottom == 0);
  REQUIRE(padding.left == 0);
}

TEST_CASE("Stock max size", "[widget]") {
  Stock w = Stock();
  const Gctx g = DebugGctx();
  w.repaint(g);

  SECTION("Maximum size is consistent with Gctx bounds") {
    REQUIRE(w.maxWidth() == g.w);
    REQUIRE(w.maxHeight() == g.h);
  }
}

TEST_CASE("Stock min size", "[widget]") {
  Stock w = Stock();
  const Gctx g = DebugGctx();
  w.repaint(g);

  SECTION("Set minimum size to greater than Gctx bounds") {
    const unsigned int minWidth = g.w + 15.0f;
    const unsigned int minHeight = g.h + 20.0f;

    w.minSize = {minWidth, minHeight};
    w.repaint(g);

    REQUIRE(w.maxWidth() == g.w);
    REQUIRE(w.maxHeight() == g.h);
  }
}
