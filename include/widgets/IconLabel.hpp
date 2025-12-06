#pragma once
#include <memory>
#include <utility>
#include "../core/Align.hpp"
#include "Icon.hpp"
#include "Label.hpp"

namespace katzen {
struct IconLabel : Widget {
  struct Builder;

  Label label{};
  Icon icon{};
  int spacing{0};
  Align valign{Align::CENTER};

  IconLabel() = default;

  IconLabel(Icon &&icon,
            Label &&label,
            int spacing = 0,
            Align valign = Align::CENTER);

  template <typename E>
  IconLabel(E icon,
            const char *text = "",
            int spacing = 0,
            Align valign = Align::CENTER)
      : label(text), icon(icon), spacing(spacing), valign(valign) {}

  void resize(Gctx g) override;
  void reposition(Vec2 position) override;
  void draw(Dctx &d) override;

  struct Builder : WidgetBuilder<Builder> {
    template <typename... Args>
    constexpr Builder &icon(Args &&...args) {
      m_icon = std::make_unique<Icon>(std::forward<Args>(args)...);
      return *this;
    }

    template <typename... Args>
    constexpr Builder &label(Args &&...args) {
      m_label = std::make_unique<Label>(std::forward<Args>(args)...);
      return *this;
    }

    constexpr Builder &spacing(int value) {
      m_spacing = value;
      return *this;
    }

    constexpr Builder &valign(Align value) {
      m_valign = value;
      return *this;
    }

    IconLabel build() const;

  private:
    int m_spacing{0};
    Align m_valign{Align::CENTER};
    std::unique_ptr<Label> m_label{};
    std::unique_ptr<Icon> m_icon{};
  };
};
} // namespace katzen
