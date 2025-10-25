#include <catch2/catch_test_macros.hpp>
#include "../../include/core/Rect.hpp"

using katzen::Rect;

TEST_CASE("Equality operators", "[rect]") {
  SECTION("Rects are equal") {
    const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
    const Rect r2{1.0f, 2.0f, 40.0f, 90.0f};

    REQUIRE(r1 == r2);
    REQUIRE(!(r1 != r2));
  }

  SECTION("Rects are not equal") {
    const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
    const Rect r2{2.0f, 2.0f, 40.0f, 80.0f};

    REQUIRE(r1 != r2);
    REQUIRE(!(r1 == r2));
  }

  SECTION("Rects are aliases") {
    const Rect r1{1.0f, 2.0f, 40.0f, 90.0f};
    const Rect &r2 = r1;

    REQUIRE(r1 == r1);
    REQUIRE(!(r1 != r1));

    REQUIRE(r1 == r2);
    REQUIRE(!(r1 != r2));
  }
}

TEST_CASE("Get position by axis", "[rect]") {
  const Rect rect{1.0f, 2.0f, 40.0f, 90.0f};

  REQUIRE(rect.position(katzen::Axis::X) == 1.0f);
  REQUIRE(rect.position(katzen::Axis::Y) == 2.0f);
}

TEST_CASE("Set position by axis", "[rect]") {
  SECTION("Set position by x-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.position(katzen::Axis::X, 10.0f);

    const Rect expected{10.0f, 2.0f, 40.0f, 90.0f};
    REQUIRE(rect == expected);
  }

  SECTION("Set position by y-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.position(katzen::Axis::Y, 10.0f);

    const Rect expected{1.0f, 10.0f, 40.0f, 90.0f};
    REQUIRE(rect == expected);
  }
}

TEST_CASE("Get size by axis", "[rect]") {
  const Rect rect{1.0f, 2.0f, 40.0f, 90.0f};

  REQUIRE(rect.size(katzen::Axis::X) == 40.0f);
  REQUIRE(rect.size(katzen::Axis::Y) == 90.0f);
}

TEST_CASE("Set size by axis", "[rect]") {
  SECTION("Set size by x-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.size(katzen::Axis::X, 10.0f);

    const Rect expected{1.0f, 2.0f, 10.0f, 90.0f};
    REQUIRE(rect == expected);
  }

  SECTION("Set size by y-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.size(katzen::Axis::Y, 10.0f);

    const Rect expected{1.0f, 2.0f, 40.0f, 10.0f};
    REQUIRE(rect == expected);
  }
}

TEST_CASE("Translate x and y", "[rect]") {
  Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
  rect.translate(5.0f, 5.0f);

  const Rect expected{6.0f, 7.0f, 40.0f, 90.0f};
  REQUIRE(rect == expected);
}

TEST_CASE("Translate by axis", "[rect]") {
  SECTION("Translate by x-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translate(katzen::Axis::X, 5.0f);

    const Rect expected{6.0f, 2.0f, 40.0f, 90.0f};
    REQUIRE(rect == expected);
  }

  SECTION("Translate by y-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translate(katzen::Axis::Y, -5.0f);

    const Rect expected{1.0f, -3.0f, 40.0f, 90.0f};
    REQUIRE(rect == expected);
  }
}

TEST_CASE("Clip width and height", "[rect]") {
  Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
  rect.clip(10.0f, -20.0f);

  const Rect expected{1.0f, 2.0f, 30.0f, 110.0f};
  REQUIRE(rect == expected);
}

TEST_CASE("Clip by axis", "[rect]") {
  SECTION("Clip by x-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.clip(katzen::Axis::X, 5.0f);

    const Rect expected{1.0f, 2.0f, 35.0f, 90.0f};
    REQUIRE(rect == expected);
  }

  SECTION("Clip by y-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.clip(katzen::Axis::Y, -5.0f);

    const Rect expected{1.0f, 2.0f, 40.0f, 95.0f};
    REQUIRE(rect == expected);
  }
}

TEST_CASE("Translate clip", "[rect]") {
  Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
  rect.translateClip(10.0f, -20.0f);

  const Rect expected{11.0f, -18.0f, 30.0f, 110.0f};
  REQUIRE(rect == expected);
}

TEST_CASE("Translate clip by axis", "[rect]") {
  SECTION("Translate clip by x-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translateClip(katzen::Axis::X, 5.0f);

    const Rect expected{6.0f, 2.0f, 35.0f, 90.0f};
    REQUIRE(rect == expected);
  }

  SECTION("Translate clip by y-axis") {
    Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translateClip(katzen::Axis::Y, -5.0f);

    const Rect expected{1.0f, -3.0f, 40.0f, 95.0f};
    REQUIRE(rect == expected);
  }
}

TEST_CASE("Pad Rect", "[rect]") {
  Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
  const katzen::Edges padding{1, 2, 5, 1};
  rect.pad(padding);

  const Rect expected{2.0f, 3.0f, 37.0f, 84.0f};
  REQUIRE(rect == expected);
}

TEST_CASE("Expand Rect", "[rect]") {
  Rect rect{1.0f, 2.0f, 40.0f, 90.0f};
  const katzen::Edges margin{1, 2, 5, 1};
  rect.expand(margin);

  const Rect expected{0.0f, 1.0f, 43.0f, 96.0f};
  REQUIRE(rect == expected);
}
