#pragma once
#include "../core/Edges.hpp"
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

  // Set all padding values.
  constexpr DerivedT &padding(Edges value) {
    m_padding = value;
    return *static_cast<DerivedT *>(this);
  }

protected:
  Edges m_padding{};
  BVec2 m_expand{};

  constexpr void setWidgetProps(Widget &widget) const {
    widget.expand = m_expand;
    widget.padding = m_padding;
  }
};
} // namespace katzen
