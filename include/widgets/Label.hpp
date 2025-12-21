#ifndef KATZE_WIDGETS_LABEL_HPP
#define KATZE_WIDGETS_LABEL_HPP

#include "Widget.hpp"

struct TTF_Text;

namespace katze {
struct Label : Widget {
  const char *text{""};
  bool wrapWords{true};

  Label(const char *text = "", bool willWrap = true)
    : text(text), wrapWords(willWrap) {}

  ~Label();

  constexpr bool empty() const { return !text || text[0] == '\0'; }

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;

protected:
  TTF_Text *textPtr{nullptr};

  void resizeForFont(Font font, const Gctx &g, FRect &rect);
  void viewForFont(Font font, Dctx &d, FRect rect);
  void viewNoTextPtr(Font font, Dctx &d, FRect rect);
};
} // namespace katze

#endif // !KATZE_WIDGETS_LABEL_HPP
