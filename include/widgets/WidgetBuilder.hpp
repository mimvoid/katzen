#pragma once
#include "../core/Edges.hpp"
#include "../core/vectors.hpp"
#include "Widget.hpp"

namespace katzen {
struct WidgetBuilder {
  // Set whether to expand horizontally within its parent.
  constexpr WidgetBuilder &hexpand(bool value) {
    m_expand.x = value;
    return *this;
  }

  // Set whether to expand vertically within its parent.
  constexpr WidgetBuilder &vexpand(bool value) {
    m_expand.y = value;
    return *this;
  }

  // Set whether to expand vertically and horizontally within its parent.
  constexpr WidgetBuilder &expand(BVec2 value) {
    m_expand = value;
    return *this;
  }

  // Set the minimum width the widget can shrink to.
  constexpr WidgetBuilder &minWidth(unsigned int value) {
    m_minSize.x = value;
    return *this;
  }

  // Set the minimum height the widget can shrink to.
  constexpr WidgetBuilder &minHeight(unsigned int value) {
    m_minSize.y = value;
    return *this;
  }

  // Set the minimum size the widget can shrink to.
  constexpr WidgetBuilder &minSize(UVec2 value) {
    m_minSize = value;
    return *this;
  }

  // Set all padding values.
  constexpr WidgetBuilder &padding(Edges value) {
    m_padding = value;
    return *this;
  }

protected:
  BVec2 m_expand{false, false};
  UVec2 m_minSize{0, 0};
  Edges m_padding{0, 0, 0, 0};

  constexpr void setWidgetProps(Widget &widget) const {
    widget.expand = m_expand;
    widget.minSize = m_minSize;
    widget.padding = m_padding;
  }
};
} // namespace katzen
