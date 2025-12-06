#pragma once
#include "../core/BVec2.hpp"
#include "../core/Edges.hpp"
#include "../core/Rect.hpp"
#include "../core/vectors.hpp"
#include "../root/Dctx.hpp"
#include "../root/Gctx.hpp"

namespace katzen {
/**
 * A basic widget for a retained mode GUI library.
 */
struct Widget {
  // Containers may access internals to manage children with less overhead.
  friend struct Box;

  constexpr Widget(Edges padding = {}, BVec2 expand = {})
    : padding(padding), expand(expand) {}

  virtual ~Widget() = default;

  Edges padding{};
  BVec2 expand{};

  /*******************/
  /* Position & Size */
  /*******************/

  // Get a rectangle with the widget's retained position and size.
  constexpr Rect rect() const { return m_rect; }

  // Get the retained x-coordinate.
  constexpr float x() const { return m_rect.x; }

  // Get the retained y-coordinate.
  constexpr float y() const { return m_rect.y; }

  // Get the retained width.
  constexpr float width() const { return m_rect.w; }

  // Get the retained height.
  constexpr float height() const { return m_rect.h; }

  // Get the size on the x-axis (width) or y-axis (height).
  constexpr float size(Axis axis) const { return m_rect.size(axis); }

  /**********/
  /* Render */
  /**********/

  // Update the size of the widget and its children, if any.
  virtual void resize(Gctx g);

  // Position the widget and relatively position its children, if any.
  virtual void reposition(Vec2 position);

  // Render the widget on the screen at its retained position.
  virtual void draw(Dctx &d) = 0;

protected:
  // The actual position and size of the widget, regardless of other factors
  // like expansion. Note that this includes padding.
  Rect m_rect{};
};
} // namespace katzen
