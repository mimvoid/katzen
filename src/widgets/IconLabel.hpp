#pragma once
#include "Icon.hpp"
#include "Label.hpp"

namespace katzen::widgets {
struct IconLabel : Widget {
  const static int spacing = 4;
  Icon icon;
  Label label;

  IconLabel(int iconId, const Font &font, std::string_view text);
  IconLabel(int iconId, const Font &font, std::string_view text, float size);

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen::widgets
