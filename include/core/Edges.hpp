#pragma once
#include <cstdint>
#include "Axis.hpp"

namespace katzen {
enum class Edge : uint8_t { TOP, RIGHT, BOTTOM, LEFT };

struct Edges {
  int top{0};
  int right{0};
  int bottom{0};
  int left{0};

  constexpr Edges(int top, int right, int bottom, int left) noexcept
      : top(top), right(right), bottom(bottom), left(left) {}

  constexpr Edges(int y, int x) noexcept : Edges(y, x, y, x) {}
  constexpr Edges(int val) noexcept : Edges(val, val) {}
  constexpr Edges() noexcept {}

  constexpr bool operator==(const Edges &other) const {
    return (top == other.top) && (right == other.right)
           && (bottom == other.bottom) && (left == other.left);
  }
  constexpr bool operator!=(const Edges &other) const {
    return !(*this == other);
  }

  constexpr int get(Edge edge) const {
    switch (edge) {
    case Edge::TOP:    return top;
    case Edge::RIGHT:  return right;
    case Edge::BOTTOM: return bottom;
    default:           return left;
    }
  }

  /**
   * Gets the sum of the values by axis.
   */
  constexpr int getSum(Axis axis) const {
    switch (axis) {
    case Axis::X: return left + right;
    case Axis::Y: return top + bottom;
    }
  }

  constexpr void set(Edge edge, int value) {
    switch (edge) {
    case Edge::TOP:    top = value; break;
    case Edge::RIGHT:  right = value; break;
    case Edge::BOTTOM: bottom = value; break;
    case Edge::LEFT:   left = value; break;
    }
  }

  /**
   * Assigns all edges to one value.
   *
   * @param value The value to assign
   */
  constexpr void set(int value) {
    top = value;
    right = value;
    bottom = value;
    left = value;
  }

  /**
   * Assigns all edge values by axis.
   *
   * @param y The value for the top and bottom
   * @param x The value for left and right
   */
  constexpr void set(int y, int x) {
    top = y;
    right = x;
    bottom = y;
    left = x;
  }
};

#ifdef DOCTEST_LIBRARY_INCLUDED
TEST_CASE("[katzen] Test Edges") {
  SUBCASE("Equality") {
    const Edges e1{1, 2, 3, 4};

    SUBCASE("Edges are equal") {
      const Edges e2{1, 2, 3, 4};
      REQUIRE(e1 == e2);
      REQUIRE(!(e1 != e2));
    }

    SUBCASE("Edges are not equal") {
      const Edges e2{2, 4, 1, 4};
      REQUIRE(e1 != e2);
      REQUIRE(!(e1 == e2));
    }

    SUBCASE("Edges are aliases") {
      const Edges &e2 = e1;
      REQUIRE(e1 == e1);
      REQUIRE(!(e1 != e1));
      REQUIRE(e1 == e2);
      REQUIRE(!(e1 != e2));
    }
  }

  SUBCASE("Construct Edges") {
    REQUIRE(Edges() == Edges{0, 0, 0, 0});
    REQUIRE(Edges(1) == Edges{1, 1, 1, 1});
    REQUIRE(Edges(1, 2) == Edges{1, 2, 1, 2});
    REQUIRE(Edges(1, 2, 3, 4) == Edges{1, 2, 3, 4});
  }

  SUBCASE("Get Edges value by enum") {
    const Edges edges{1, 2, 3, 4};

    CHECK(edges.get(Edge::TOP) == 1);
    CHECK(edges.get(Edge::RIGHT) == 2);
    CHECK(edges.get(Edge::BOTTOM) == 3);
    CHECK(edges.get(Edge::LEFT) == 4);
  }

  SUBCASE("Set Edges value by enum") {
    SUBCASE("Top field value") {
      Edges edges{1, 2, 3, 4};
      edges.set(Edge::TOP, 0);
      CHECK(edges == Edges{0, 2, 3, 4});
    }

    SUBCASE("Right field value") {
      Edges edges{1, 2, 3, 4};
      edges.set(Edge::RIGHT, 0);
      CHECK(edges == Edges{1, 0, 3, 4});
    }

    SUBCASE("Bottom field value") {
      Edges edges{1, 2, 3, 4};
      edges.set(Edge::BOTTOM, 0);
      CHECK(edges == Edges{1, 2, 0, 4});
    }

    SUBCASE("Left field value") {
      Edges edges{1, 2, 3, 4};
      edges.set(Edge::LEFT, 0);
      CHECK(edges == Edges{1, 2, 3, 0});
    }
  }

  SUBCASE("Get Edges values by axis") {
    const Edges edges{1, 2, 3, 4};

    CHECK(edges.getSum(katzen::Axis::X) == 6);
    CHECK(edges.getSum(katzen::Axis::Y) == 4);
  }

  SUBCASE("Set Edges field values") {
    SUBCASE("One value") {
      Edges edges{1, 2, 3, 4};
      edges.set(5);
      CHECK(edges == Edges{5, 5, 5, 5});
    }

    SUBCASE("Two values") {
      Edges edges{1, 2, 3, 4};
      edges.set(5, 6);
      CHECK(edges == Edges{5, 6, 5, 6});
    }
  }
}
#endif
} // namespace katzen
