#pragma once
#include "../core/Edges.hpp"
#include "../core/vectors.hpp"
#include "Widget.hpp"

namespace katzen {
template <class DerivedT>
struct WidgetBuilder {
  // Set whether to expand horizontally within its parent.
  constexpr DerivedT &hexpand(bool value) {
    m_expand.x = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set whether to expand vertically within its parent.
  constexpr DerivedT &vexpand(bool value) {
    m_expand.y = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set whether to expand vertically and horizontally within its parent.
  constexpr DerivedT &expand(BVec2 value) {
    m_expand = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set the minimum width the widget can shrink to.
  constexpr DerivedT &minWidth(unsigned int value) {
    m_minSize.x = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set the minimum height the widget can shrink to.
  constexpr DerivedT &minHeight(unsigned int value) {
    m_minSize.y = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set the minimum size the widget can shrink to.
  constexpr DerivedT &minSize(UVec2 value) {
    m_minSize = value;
    return *static_cast<DerivedT *>(this);
  }

  // Set all padding values.
  constexpr DerivedT &padding(Edges value) {
    m_padding = value;
    return *static_cast<DerivedT *>(this);
  }

protected:
  BVec2 m_expand{};
  UVec2 m_minSize{};
  Edges m_padding{};

  constexpr void setWidgetProps(Widget &widget) const {
    widget.expand = m_expand;
    widget.minSize = m_minSize;
    widget.padding = m_padding;
  }
};
} // namespace katzen
