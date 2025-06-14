#pragma once
#include "Icon.hpp"
#include "Label.hpp"

namespace katzen {
struct IconLabel : Widget {
  const static int spacing = 4;
  Icon icon;
  Label label;

  IconLabel(uint8_t iconId, const Font &font, std::string_view text);

  template <typename E>
  IconLabel(E enumIconId, const Font &font, std::string_view text);

  IconLabel(uint8_t iconId, const Font &font, std::string_view text, float size);

  template <typename E>
  IconLabel(E enumIconId, const Font &font, std::string_view text, float size);

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen::widgets
