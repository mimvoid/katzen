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

  int spacing;
  Axis direction;
  AlignVec2 align;

  Box(int spacing = 0,
      Axis direction = Axis::X,
      Align halign = Align::START,
      Align valign = Align::START)
      : spacing(spacing), direction(direction), align(halign, valign) {}

  void resize(Gctx g) override;
  void reposition(Vec2 position) override;
  void draw(Dctx &d) override;

protected:
  float m_expandedSize{0.0f};

  Vec2 resizeChildren(Gctx g);
  void positionChildren(Vec2 childrenSize);

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
      m_align.x = value;
      return *this;
    }

    constexpr Builder &valign(Align value) {
      m_align.y = value;
      return *this;
    }

    constexpr Builder &align(Align halign, Align valign) {
      m_align = {halign, valign};
      return *this;
    }

    Box build() const {
      Box box(m_spacing, m_direction, m_align.x, m_align.y);
      box.m_children = std::move(m_children);
      setWidgetProps(box);
      return box;
    }

  private:
    int m_spacing{0};
    Axis m_direction{Axis::X};
    AlignVec2 m_align{};
  };
};
} // namespace katzen
