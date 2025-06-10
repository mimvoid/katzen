#include <catch2/catch_test_macros.hpp>
#include "../../src/core/Align.hpp"

using katzen::Align;
using katzen::offset;

TEST_CASE("Start align offset", "[align]") {
  SECTION("Child is smaller than the parent") {
    REQUIRE(offset(50.0f, 25.0f, Align::START) == 0.0f);
  }

  SECTION("Child is the same size as the parent") {
    REQUIRE(offset(50.0f, 50.0f, Align::START) == 0.0f);
  }

  SECTION("Child is bigger than the parent") {
    REQUIRE(offset(50.0f, 60.0f, Align::START) == 0.0f);
  }
}

TEST_CASE("Center align offset", "[align]") {
  SECTION("Child is smaller than the parent") {
    REQUIRE(offset(60.0f, 20.0f, Align::CENTER) == 20.0f);
  }

  SECTION("Child is the same size as the parent") {
    REQUIRE(offset(50.0f, 50.0f, Align::CENTER) == 0.0f);
  }

  SECTION("Child is bigger than the parent") {
    REQUIRE(offset(40.0f, 60.0f, Align::CENTER) == -10.0f);
  }
}

TEST_CASE("End align offset", "[align]") {
  SECTION("Child is smaller than the parent") {
    REQUIRE(offset(60.0f, 20.0f, Align::END) == 40.0f);
  }

  SECTION("Child is the same size as the parent") {
    REQUIRE(offset(50.0f, 50.0f, Align::END) == 0.0f);
  }

  SECTION("Child is bigger than the parent") {
    REQUIRE(offset(40.0f, 60.0f, Align::END) == -20.0f);
  }
}

TEST_CASE("Offset with negative sizes", "[align]") {
  SECTION("Parent size is negative") {
    REQUIRE(offset(-10.0f, 20.0f, Align::START) == 0.0f);
    REQUIRE(offset(-10.0f, 20.0f, Align::CENTER) == -10.0f);
    REQUIRE(offset(-10.0f, 20.0f, Align::END) == -20.0f);
  }

  SECTION("Child size is negative") {
    REQUIRE(offset(20.0f, -10.0f, Align::START) == 0.0f);
    REQUIRE(offset(20.0f, -10.0f, Align::CENTER) == 10.0f);
    REQUIRE(offset(20.0f, -10.0f, Align::END) == 20.0f);
  }

  SECTION("Parent and child sizes are negative") {
    REQUIRE(offset(-20.0f, -10.0f, Align::START) == 0.0f);
    REQUIRE(offset(-20.0f, -10.0f, Align::CENTER) == 0.0f);
    REQUIRE(offset(-20.0f, -10.0f, Align::END) == 0.0f);
  }
}
