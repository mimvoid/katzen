#include <catch2/catch_test_macros.hpp>
#include "../../icons/katz_icons.hpp"
#include "../../src/widgets/Icon.hpp"

using katzen::Gctx;
using katzen::KatzIcon;
using katzen::Icon;

TEST_CASE("Initial fields", "[icon]") {
  const Icon withName(KatzIcon::ALARM_CLOCK);
  REQUIRE(withName.getId() == static_cast<uint8_t>(KatzIcon::ALARM_CLOCK));
  REQUIRE(withName.scale() == 1);

  const Icon withSize(KatzIcon::FILE, 2);
  REQUIRE(withSize.getId() == static_cast<uint8_t>(KatzIcon::FILE));
  REQUIRE(withSize.scale() == 2);
}

TEST_CASE("Set icon size, within bounds", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.scale(2);
  REQUIRE(icon.scale() == 2);
}

TEST_CASE("Try setting icon size of 0", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.scale(0);
  REQUIRE(icon.scale() == 1);
}

TEST_CASE("Try setting negative icon size", "[icon]") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.scale(-2);
  REQUIRE(icon.scale() == 1);
}

TEST_CASE("Measure icon size", "[icon]") {
  Icon icon(KatzIcon::WAVE);
  icon.padding.set(0);
  icon.repaint(Gctx::init());

  const int iconSize = icon.scale() * RAYGUI_ICON_SIZE;
  REQUIRE(icon.width() == iconSize);
  REQUIRE(icon.height() == iconSize);
}
