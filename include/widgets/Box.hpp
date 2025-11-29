#pragma once
#include <utility>
#include "../core/Align.hpp"
#include "../parts/Container.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that contains other widgets.
 * It handles their sizes and alignments.
 */
struct Box : Widget, Container {
  struct Builder;

  int spacing{0};
  Axis direction{Axis::X};
  Align halign{Align::START};
  Align valign{Align::START};

  Box(int spacing = 0,
      Axis direction = Axis::X,
      Align halign = Align::START,
      Align valign = Align::START)
      : spacing(spacing),
        direction(direction),
        halign(halign),
        valign(valign) {}

  void repaint(Gctx &g) override;
  void draw(Dctx &d) override;

protected:
  Vec2 remeasureChildren();
  float measureChildren(Axis axis) const;
  float measure(Axis a) const override;

  constexpr Align align(Axis axis) const {
    switch (axis) {
    case Axis::X: return halign;
    case Axis::Y: return valign;
    }
  }

public:
  struct Builder : WidgetBuilder<Builder>, ContainerBuilder<Builder> {
    constexpr Builder &spacing(int value) {
      m_spacing = value;
      return *this;
    }

    constexpr Builder &direction(Axis value) {
      m_direction = value;
      return *this;
    }

    constexpr Builder &halign(Align value) {
      m_halign = value;
      return *this;
    }

    constexpr Builder &valign(Align value) {
      m_valign = value;
      return *this;
    }

    Box build() const {
      Box box(m_spacing, m_direction);
      box.halign = m_halign;
      box.valign = m_valign;
      box.m_children = std::move(m_children);
      setWidgetProps(box);
      return box;
    }

  private:
    int m_spacing{0};
    Axis m_direction{Axis::X};
    Align m_halign{Align::START};
    Align m_valign{Align::START};
  };
};
} // namespace katzen
