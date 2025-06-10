#include <catch2/catch_test_macros.hpp>
#include "../../src/core/Bounds.hpp"

using katzen::Bounds;

TEST_CASE("Equality operators", "[bounds]") {
  SECTION("Bounds are equal") {
    const Bounds b1{{0, 1}, {60, 80}};
    const Bounds b2{{0, 1}, {60, 80}};

    REQUIRE(b1 == b2);
    REQUIRE(!(b1 != b2));
  }

  SECTION("Bounds are not equal") {
    const Bounds b1{{0, 1}, {60, 80}};
    const Bounds b2{{0, 1}, {61, 80}};

    REQUIRE(b1 != b2);
    REQUIRE(!(b1 == b2));
  }

  SECTION("Bounds are aliases") {
    const Bounds b1{{0, 1}, {60, 80}};
    const Bounds &b2 = b1;

    REQUIRE(b1 == b1);
    REQUIRE(!(b1 != b1));

    REQUIRE(b1 == b2);
    REQUIRE(!(b1 != b2));
  }
}

TEST_CASE("Set minimum width", "[bounds]") {
  SECTION("New minimum width is less than maximum width") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minWidth(10);

    const Bounds expected{{10, 0}, {80, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New minimum width is equal to maximum width") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minWidth(80);

    const Bounds expected{{80, 0}, {80, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New minimum width is greater than maximum width") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minWidth(100);

    const Bounds expected{{100, 0}, {100, 80}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set minimum height", "[bounds]") {
  SECTION("New minimum height is less than maximum height") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minHeight(10);

    const Bounds expected{{0, 10}, {80, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New minimum height is equal to maximum height") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minHeight(80);

    const Bounds expected{{0, 80}, {80, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New minimum height is greater than maximum height") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.minHeight(100);

    const Bounds expected{{0, 100}, {80, 100}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set maximum width", "[bounds]") {
  SECTION("New maximum width is greater than minimum width") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.maxWidth(10);

    const Bounds expected{{0, 0}, {10, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New maximum width is equal to minimum width") {
    Bounds bounds{{10, 10}, {80, 80}};
    bounds.maxWidth(10);

    const Bounds expected{{10, 10}, {10, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New maximum width is less than minimum width") {
    Bounds bounds{{10, 10}, {80, 80}};
    bounds.maxWidth(5);

    const Bounds expected{{5, 10}, {5, 80}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set maximum height", "[bounds]") {
  SECTION("New maximum height is greater than minimum height") {
    Bounds bounds{{0, 0}, {80, 80}};
    bounds.maxHeight(10);

    const Bounds expected{{0, 0}, {80, 10}};
    REQUIRE(bounds == expected);
  }

  SECTION("New maximum height is equal to minimum height") {
    Bounds bounds{{10, 10}, {80, 80}};
    bounds.maxHeight(10);

    const Bounds expected{{10, 10}, {80, 10}};
    REQUIRE(bounds == expected);
  }

  SECTION("New maximum height is less than minimum height") {
    Bounds bounds{{10, 10}, {80, 80}};
    bounds.maxHeight(5);

    const Bounds expected{{10, 5}, {80, 5}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set minimum sizes", "[bounds]") {
  SECTION("New minimum sizes are less than maximum sizes") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMin(10, 20);

    const Bounds expected{{10, 20}, {60, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("New minimum sizes are greater than maximum sizes") {
    Bounds bounds{{10, 20}, {60, 80}};
    bounds.setMin(100, 100);

    const Bounds expected{{100, 100}, {100, 100}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set maximum sizes", "[bounds]") {
  SECTION("New maximum sizes are greater than minimum sizes") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMax(10, 20);

    const Bounds expected{{0, 10}, {10, 20}};
    REQUIRE(bounds == expected);
  }

  SECTION("New maximum sizes are less than minimum sizes") {
    Bounds bounds{{10, 20}, {60, 80}};
    bounds.setMax(5, 10);

    const Bounds expected{{5, 10}, {5, 10}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set minimum size by axis", "[bounds]") {
  SECTION("Set minimum size by x-axis") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMin(katzen::Axis::X, 40);

    const Bounds expected{{40, 10}, {60, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("Set minimum size by y-axis") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMin(katzen::Axis::Y, 100);

    const Bounds expected{{0, 100}, {60, 100}};
    REQUIRE(bounds == expected);
  }
}

TEST_CASE("Set maximum size by axis", "[bounds]") {
  SECTION("Set maximum size by x-axis") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMax(katzen::Axis::X, 40);

    const Bounds expected{{0, 10}, {40, 80}};
    REQUIRE(bounds == expected);
  }

  SECTION("Set maximum size by y-axis") {
    Bounds bounds{{0, 10}, {60, 80}};
    bounds.setMax(katzen::Axis::Y, 5);

    const Bounds expected{{0, 5}, {60, 5}};
    REQUIRE(bounds == expected);
  }
}
