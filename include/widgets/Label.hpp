#pragma once
#include "parts/Text.hpp"
#include "theme/fonts.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that displays text.
 */
struct Label : Widget {
  struct Builder : WidgetBuilder<Builder> {
    Builder(FontStyle &style = theme::fontStyle()) : m_text("", style) {}

    constexpr Builder &wrapWords(bool value) {
      m_wrapWords = value;
      return *this;
    }

    constexpr Builder &content(const char *value) {
      m_text.content = value;
      return *this;
    }

    constexpr Builder &fontStyle(FontStyle &value) {
      m_text.style = value;
      return *this;
    }

    Label build() const {
      Label label(m_text, m_wrapWords);
      setWidgetProps(label);
      return label;
    }

  private:
    Text m_text;
    bool m_wrapWords{true};
  };

  Text text;
  bool wrapWords{true};

  Label(const char *content,
        bool wrapWords = true,
        FontStyle &style = theme::fontStyle())
      : text(content, style), wrapWords(wrapWords) {}

  Label(Text text, bool wrapWords = true) : text(text), wrapWords(wrapWords) {}

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;

  constexpr bool willWrap() const {
    return wrapWords && (text.width() + padding.getSum(Axis::X) > maxWidth());
  }
};
} // namespace katzen
