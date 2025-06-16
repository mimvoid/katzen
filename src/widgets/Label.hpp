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
  friend struct IconLabel;

  Text text;
  bool wrapWords;

  Label(std::string_view content,
        bool wrapWords = true,
        std::size_t fontId = theme::defaultFontId(),
        std::function<void(Label &)> setup = std::function<void(Label &)>());

  constexpr bool willWrap() const {
    return wrapWords && (text.width() + padding.get(Axis::X) > maxWidth());
  }

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measureSize(Axis axis) const override;
};
} // namespace katzen
