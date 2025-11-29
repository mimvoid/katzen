#include <doctest/doctest.h>
#include "icons/katz_icons.hpp"
#include "widgets/Icon.hpp"

namespace katzen {
TEST_CASE("[katzen] Icon initial fields") {
  const Icon withName(KatzIcon::ALARM_CLOCK);
  REQUIRE(withName.icon == static_cast<uint8_t>(KatzIcon::ALARM_CLOCK));
  REQUIRE(withName.scale() == 1);

  const Icon withSize(KatzIcon::FILE, 2);
  REQUIRE(withSize.icon == static_cast<uint8_t>(KatzIcon::FILE));
  REQUIRE(withSize.scale() == 2);
}

TEST_CASE("[katzen] Set Icon size, within bounds") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.setScale(2);
  CHECK(icon.scale() == 2);
}

TEST_CASE("[katzen] Try setting Icon size of 0") {
  Icon icon(KatzIcon::ALARM_CLOCK);
  icon.setScale(0);
  CHECK(icon.scale() == 1);
}

TEST_CASE("[katzen] Measure Icon size") {
  Icon icon(KatzIcon::WAVE);
  icon.padding.set(0);
  Gctx g{FontStyle{}};
  icon.repaint(g);

  const int iconSize = icon.scale() * RAYGUI_ICON_SIZE;
  CHECK(icon.width() == iconSize);
  CHECK(icon.height() == iconSize);
}
} // namespace katzen
