#include "../../src/widgets/Widget.hpp"
#include <catch2/catch_test_macros.hpp>

using katzen::Axis;
using katzen::Edges;
using katzen::Gctx;
using katzen::Rect;

// Widget is an abstract class, so create a basic child class for testing
struct Stock : katzen::Widget {
  void draw(katzen::Dctx &d) override {}
};

constexpr Gctx DebugGctx() {
  // The tests run without a window open,
  // so fake the window size
  return {0, 0, 960, 640};
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

  const glm::vec2 pos = w.position();
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

  SECTION("Getting max size by axis is consistent") {
    REQUIRE(w.maxSize(Axis::X) == w.maxWidth());
    REQUIRE(w.maxSize(Axis::Y) == w.maxHeight());
  }

  SECTION("Set maximum size to less than Gctx bounds") {
    const float newMaxWidth = g.w - 15.0f;
    const float newMaxHeight = g.h - 20.0f;

    w.bounds.max.x = newMaxWidth;
    w.bounds.max.y = newMaxHeight;
    w.repaint(g);

    REQUIRE(w.maxWidth() == newMaxWidth);
    REQUIRE(w.maxHeight() == newMaxHeight);
  }
}

TEST_CASE("Stock min size", "[widget]") {
  Stock w = Stock();
  const Gctx g = DebugGctx();
  w.repaint(g);

  SECTION("Minimum size is 0 by default") {
    REQUIRE(w.bounds.min.x == 0);
    REQUIRE(w.bounds.min.y == 0);
  }

  SECTION("Getting min size by axis is consistent") {
    REQUIRE(w.minSize(Axis::X) == w.bounds.min.x);
    REQUIRE(w.minSize(Axis::Y) == w.bounds.min.y);
  }

  SECTION("Set minimum size to greater than Gctx bounds") {
    const unsigned int minWidth = g.w + 15.0f;
    const unsigned int minHeight = g.h + 20.0f;

    w.bounds.min.x = minWidth;
    w.bounds.min.y = minHeight;
    w.repaint(g);

    REQUIRE(w.maxWidth() == minWidth);
    REQUIRE(w.maxHeight() == minHeight);
  }
}
