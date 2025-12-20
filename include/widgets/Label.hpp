#ifndef KATZE_WIDGETS_LABEL_HPP
#define KATZE_WIDGETS_LABEL_HPP

#include "Widget.hpp"

namespace katze {
struct Label : Widget {
  const char *text{""};
  bool wrapWords{true};

  Label(const char *text = "", bool willWrap = true)
    : text(text), wrapWords(willWrap) {}

  constexpr bool empty() const { return !text || text[0] == '\0'; }

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_LABEL_HPP
