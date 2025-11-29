#pragma once
#include "../core/vectors.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that displays text.
 */
struct Label : Widget {
  struct Builder;

  const char *text;
  bool wrapWords{true};

  Label(const char *text, bool wrapWords = true)
      : text(text), wrapWords(wrapWords) {}

  constexpr bool empty() const { return !text || text[0] == '\0'; }

  void repaint(Gctx &g) override;
  void draw(Dctx &d) override;

protected:
  Vec2 textSize{};

  float measure(Axis axis) const override;

  constexpr bool willWrap() const {
    return wrapWords && (textSize.x + padding.getSum(Axis::X) > maxWidth());
  }

  void drawStyled(FontStyle &style, Color textColor);

public:
  struct Builder : WidgetBuilder<Builder> {
    constexpr Builder &wrapWords(bool value) {
      m_wrapWords = value;
      return *this;
    }

    constexpr Builder &text(const char *value) {
      m_text = value;
      return *this;
    }

    Label build() const {
      Label label(m_text, m_wrapWords);
      setWidgetProps(label);
      return label;
    }

  private:
    const char *m_text{""};
    bool m_wrapWords{true};
  };
};
} // namespace katzen
