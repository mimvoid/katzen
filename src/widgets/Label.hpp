#pragma once
#include <functional>
#include <string_view>
#include "../components/Text.hpp"
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that displays text.
 */
struct Label : Widget {
  Text text;
  bool wrapWords;

  Label(const Font &font, std::string_view text);
  Label(const Font &font, std::string_view text, float size);
  Label(std::function<void(Label &)> setup,
        const Font &font,
        std::string_view text,
        float size);

  constexpr bool willWrap() const {
    return wrapWords && (text.width() + padding.get(Axis::X) > maxWidth());
  }

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen
