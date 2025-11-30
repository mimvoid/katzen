#pragma once
#include "../theme/FontStyle.hpp"
#include "Label.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that displays custom styled text.
 */
struct LabelEx : Label {
  struct Builder;
  FontStyle style{};

  LabelEx(const char *content, FontStyle style, bool wrapWords = true)
      : Label(content, wrapWords), style(style) {}

  void resize(Gctx g) override;
  void draw(Dctx &d) override;

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

    constexpr Builder &fontStyle(FontStyle value) {
      style = value;
      return *this;
    }

    LabelEx build() const {
      LabelEx label(m_text, style, m_wrapWords);
      setWidgetProps(label);
      return label;
    }

  private:
    const char *m_text{""};
    FontStyle style{};
    bool m_wrapWords{true};
  };
};
} // namespace katzen
