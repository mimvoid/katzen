#define RAYGUI_IMPLEMENTATION
#include "../../src/widgets/Icon.hpp"
#include <catch2/catch_test_macros.hpp>

using katzen::widgets::Icon;
using katzen::Gctx;

TEST_CASE("Initial fields", "[icon]") {
  const Icon withName(ICON_ALARM);
  REQUIRE(withName.iconId == ICON_ALARM);
  REQUIRE(withName.iconSize() == 1);

  const Icon withSize(ICON_RESIZE, 2);
  REQUIRE(withSize.iconId == ICON_RESIZE);
  REQUIRE(withSize.iconSize() == 2);
}

TEST_CASE("Set icon size, within bounds", "[icon]") {
  Icon icon(ICON_ALARM);
  icon.iconSize(2);
  REQUIRE(icon.iconSize() == 2);
}

TEST_CASE("Try setting icon size of 0", "[icon]") {
  Icon icon(ICON_ALARM);
  icon.iconSize(0);
  REQUIRE(icon.iconSize() == 1);
}

TEST_CASE("Try setting negative icon size", "[icon]") {
  Icon icon(ICON_ALARM);
  icon.iconSize(-2);
  REQUIRE(icon.iconSize() == 1);
}

TEST_CASE("Empty icon", "[icon]") {
  Icon icon(ICON_NONE);
  REQUIRE(icon.empty());

  SECTION("Icon is still empty after setting icon size") {
    icon.iconSize(2);
    REQUIRE(icon.empty());
  }

  SECTION("Icon returns correct icon size once it is not empty") {
    icon.iconId = ICON_WAVE;
    REQUIRE(!icon.empty());
  }
}

TEST_CASE("Non-empty icon", "[icon]") {
  Icon icon(ICON_WAVE);
  REQUIRE(!icon.empty());

  SECTION("Make icon empty") {
    icon.iconId = ICON_NONE;
    REQUIRE(icon.empty());
  }
}

TEST_CASE("Measure non-empty icon size", "[icon]") {
  Icon icon(ICON_WAVE);
  icon.padding.set(0);
  icon.repaint(Gctx::init());

  const int iconSize = icon.iconSize() * RAYGUI_ICON_SIZE;
  REQUIRE(icon.width() == iconSize);
  REQUIRE(icon.height() == iconSize);
}

TEST_CASE("Measure empty icon size", "[icon]") {
  Icon icon(ICON_NONE);
  icon.padding.set(0);
  icon.repaint(Gctx::init());

  REQUIRE(icon.width() == 0);
  REQUIRE(icon.height() == 0);
}
