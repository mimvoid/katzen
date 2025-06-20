#pragma once
#include <functional>
#include <string_view>
#include "../components/Text.hpp"
#include "../theme/fonts.hpp"
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
        theme::FontStyle &style = theme::getFontStyle(),
        bool wrapWords = true,
        std::function<void(Label &)> setup = std::function<void(Label &)>());

  constexpr bool willWrap() const {
    return wrapWords && (text.width() + padding.get(Axis::X) > maxWidth());
  }

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;
};
} // namespace katzen
