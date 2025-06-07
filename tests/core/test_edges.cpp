#include "../../src/core/Edges.hpp"
#include <catch2/catch_test_macros.hpp>

using katzen::Edges;
using katzen::Edge;

TEST_CASE("Equality operators", "[edges]") {
  SECTION("Edges are equal") {
    const Edges e1{1, 2, 3, 4};
    const Edges e2{1, 2, 3, 4};

    REQUIRE(e1 == e2);
    REQUIRE(!(e1 != e2));
  }

  SECTION("Edges are not equal") {
    const Edges e1{1, 2, 3, 4};
    const Edges e2{2, 4, 1, 4};

    REQUIRE(e1 != e2);
    REQUIRE(!(e1 == e2));
  }

  SECTION("Edges are aliases") {
    const Edges e1{1, 2, 3, 4};
    const Edges &e2 = e1;

    REQUIRE(e1 == e1);
    REQUIRE(!(e1 != e1));
    REQUIRE(e1 == e2);
    REQUIRE(!(e1 != e2));
  }
}

TEST_CASE("Construct Edges", "[edges]") {
  SECTION("Intialize with curly braces") {
    const Edges expected{0, 0, 0, 0};
    const Edges result{};
    REQUIRE(expected == result);
  }

  SECTION("Intiialize with no values") {
    const Edges expected{0, 0, 0, 0};
    REQUIRE(Edges() == expected);
  }

  SECTION("Initialize with one value") {
    const Edges expected{1, 1, 1, 1};
    REQUIRE(Edges(1) == expected);
  }

  SECTION("Initialize with two values") {
    const Edges expected{1, 2, 1, 2};
    REQUIRE(Edges(1, 2) == expected);
  }

  SECTION("Initialize with three values") {
    const Edges expected{2, 1, 3, 1};
    REQUIRE(Edges(2, 1, 3) == expected);
  }

  SECTION("Initialize with four values") {
    const Edges expected{1, 2, 3, 4};
    REQUIRE(Edges(1, 2, 3, 4) == expected);
  }
}

TEST_CASE("Get value by enum", "[edges]") {
  const Edges edges{1, 2, 3, 4};

  REQUIRE(edges.get(Edge::TOP) == 1);
  REQUIRE(edges.get(Edge::RIGHT) == 2);
  REQUIRE(edges.get(Edge::BOTTOM) == 3);
  REQUIRE(edges.get(Edge::LEFT) == 4);
}

TEST_CASE("Set value by enum", "[edges]") {
  SECTION("Top field value") {
    Edges edges{1, 2, 3, 4};
    edges.set(Edge::TOP, 0);

    const Edges result{0, 2, 3, 4};
    REQUIRE(edges == result);
  }

  SECTION("Right field value") {
    Edges edges{1, 2, 3, 4};
    edges.set(Edge::RIGHT, 0);

    const Edges result{1, 0, 3, 4};
    REQUIRE(edges == result);
  }

  SECTION("Bottom field value") {
    Edges edges{1, 2, 3, 4};
    edges.set(Edge::BOTTOM, 0);

    const Edges result{1, 2, 0, 4};
    REQUIRE(edges == result);
  }

  SECTION("Left field value") {
    Edges edges{1, 2, 3, 4};
    edges.set(Edge::LEFT, 0);

    const Edges result{1, 2, 3, 0};
    REQUIRE(edges == result);
  }
}

TEST_CASE("Get values by axis", "[edges]") {
  const Edges edges{1, 2, 3, 4};

  REQUIRE(edges.get(katzen::Axis::X) == 6);
  REQUIRE(edges.get(katzen::Axis::Y) == 4);
}

TEST_CASE("Set field values", "[edges]") {
  SECTION("One value") {
    Edges edges{1, 2, 3, 4};
    edges.set(5);

    const Edges result{5, 5, 5, 5};
    REQUIRE(edges == result);
  }

  SECTION("Two values") {
    Edges edges{1, 2, 3, 4};
    edges.set(5, 6);

    const Edges result{5, 6, 5, 6};
    REQUIRE(edges == result);
  }

  SECTION("Three values") {
    Edges edges{1, 2, 3, 4};
    edges.set(5, 7, 6);

    const Edges result{5, 7, 6, 7};
    REQUIRE(edges == result);
  }
}
