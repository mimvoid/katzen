#pragma once
#include <cstdint>
#include "Axis.hpp"

namespace katzen {
// Edges of a rectangle.
enum class Edge : uint8_t { TOP, RIGHT, BOTTOM, LEFT };

template <typename T>
struct edges_t {
  T top{0};
  T right{0};
  T bottom{0};
  T left{0};

  constexpr edges_t(T top, T right, T bottom, T left) noexcept
      : top(top), right(right), bottom(bottom), left(left) {}

  constexpr edges_t(T y, T x) noexcept : edges_t(y, x, y, x) {}
  constexpr edges_t(T val) noexcept : edges_t(val, val) {}
  constexpr edges_t() noexcept {}

  constexpr bool operator==(const edges_t &other) const {
    return (top == other.top) && (right == other.right)
           && (bottom == other.bottom) && (left == other.left);
  }
  constexpr bool operator!=(const edges_t &other) const {
    return !(*this == other);
  }

  // Get the value of an edge.
  constexpr T get(Edge edge) const {
    switch (edge) {
    case Edge::TOP:    return top;
    case Edge::RIGHT:  return right;
    case Edge::BOTTOM: return bottom;
    default:           return left;
    }
  }

  // Set an edge's value.
  constexpr void set(Edge edge, T value) {
    switch (edge) {
    case Edge::TOP:    top = value; break;
    case Edge::RIGHT:  right = value; break;
    case Edge::BOTTOM: bottom = value; break;
    case Edge::LEFT:   left = value; break;
    }
  }

  // Get the sum of the horizontal values.
  constexpr T getX() const { return left + right; }

  // Get the sum of the vertical values.
  constexpr T getY() const { return top + bottom; }

  // Get the sum of the values by axis.
  constexpr T getSum(Axis axis) const {
    return (axis == Axis::X) ? getX() : getY();
  }

  /**
   * Assign all edges to one value.
   * @param value Value to assign
   */
  constexpr void set(T value) {
    top = value;
    right = value;
    bottom = value;
    left = value;
  }

  /**
   * Assign edge values by axis.
   * @param y Value for the top and bottom edges
   * @param x Value for left and right edges
   */
  constexpr void set(T y, T x) {
    top = y;
    right = x;
    bottom = y;
    left = x;
  }
};

typedef edges_t<int> Edges;

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
