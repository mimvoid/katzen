#include <catch2/catch_test_macros.hpp>
#include "../../icons/katz_icons.hpp"
#include "../../src/widgets/Icon.hpp"

using katzen::Gctx;
using katzen::KatzIcon;
using katzen::widgets::Icon;

TEST_CASE("Initial fields", "[icon]") {
  const Icon withName(KatzIcon::ALARM_CLOCK);
  REQUIRE(withName.iconId() == static_cast<uint8_t>(KatzIcon::ALARM_CLOCK));
  REQUIRE(withName.iconSize() == 1);

  const Icon withSize(KatzIcon::FILE, 2);
  REQUIRE(withSize.iconId() == static_cast<uint8_t>(KatzIcon::FILE));
  REQUIRE(withSize.iconSize() == 2);
}

TEST_CASE("Set icon size, within bounds", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.iconSize(2);
  REQUIRE(icon.iconSize() == 2);
}

TEST_CASE("Try setting icon size of 0", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.iconSize(0);
  REQUIRE(icon.iconSize() == 1);
}

TEST_CASE("Try setting negative icon size", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.iconSize(-2);
  REQUIRE(icon.iconSize() == 1);
}

TEST_CASE("Empty icon", "[icon]") {
  Icon icon(KatzIcon::NONE);
  REQUIRE(icon.empty());

  SECTION("Icon is still empty after setting icon size") {
    icon.iconSize(2);
    REQUIRE(icon.empty());
  }

  SECTION("Icon returns correct icon size once it is not empty") {
    icon.iconId(KatzIcon::WAVE);
    REQUIRE(!icon.empty());
  }
}

TEST_CASE("Non-empty icon", "[icon]") {
  Icon icon(KatzIcon::WAVE);
  REQUIRE(!icon.empty());

  SECTION("Make icon empty") {
    icon.iconId(KatzIcon::NONE);
    REQUIRE(icon.empty());
  }
}

TEST_CASE("Measure non-empty icon size", "[icon]") {
  Icon icon(KatzIcon::WAVE);
  icon.padding.set(0);
  icon.repaint(Gctx::init());

  const int iconSize = icon.iconSize() * RAYGUI_ICON_SIZE;
  REQUIRE(icon.width() == iconSize);
  REQUIRE(icon.height() == iconSize);
}

TEST_CASE("Measure empty icon size", "[icon]") {
  Icon icon(KatzIcon::NONE);
  icon.padding.set(0);
  icon.repaint(Gctx::init());

  REQUIRE(icon.width() == 0);
  REQUIRE(icon.height() == 0);
}
