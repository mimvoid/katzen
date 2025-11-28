#pragma once
#include <raylib.h>
#include <algorithm>
#include <climits>
#include "core/Dctx.hpp"
#include "core/Edges.hpp"
#include "core/Gctx.hpp"
#include "core/vectors.hpp"

namespace katzen {
/**
 * A basic widget for a retained mode GUI library.
 */
struct Widget {
  // Containers may access internals to manage children with less overhead.
  friend struct Box;

  virtual ~Widget() = default;

  UVec2 minSize{0, 0};
  Edges padding{0, 0, 0, 0};
  BVec2 expand{false, false};

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
  /* Bounds */
  /**********/

  constexpr unsigned int maxWidth() const { return m_bounds.x; }
  constexpr unsigned int maxHeight() const { return m_bounds.y; }

  /**********/
  /* Render */
  /**********/

  // Resize and reposition the widget and its children, if any.
  virtual void repaint(Gctx g);

  // Render the widget on the screen at its retained position.
  virtual void draw(Dctx &d) = 0;

protected:
  constexpr Widget() = default;

  Rect m_rect{0, 0, 0, 0};
  // Maximum sizes that may be overridden by repaints.
  UVec2 m_bounds{GetRenderWidth(), GetRenderHeight()};

  // Recalculate and return the size on the x-axis (width) or y-axis (height).
  virtual float measure(Axis axis) const;

  // Recalculate and return the width.
  inline float measureWidth() const { return measure(Axis::X); }

  // Recalculate and return the height.
  inline float measureHeight() const { return measure(Axis::Y); }

  // Change the retained position.
  constexpr void reposition(Vec2 p) {
    m_rect.x = p.x;
    m_rect.y = p.y;
  }

  inline void reposition(Gctx g) {
    m_rect.x = g.x;
    m_rect.y = g.y;
  }

  inline void setBounds(Gctx g) { m_bounds = {g.w, g.h}; }

  constexpr float clampSize(float size, Axis axis) const {
    switch (axis) {
    case Axis::X: return std::clamp(size, (float)minSize.x, (float)m_bounds.x);
    case Axis::Y: return std::clamp(size, (float)minSize.y, (float)m_bounds.y);
    }
  }

  // Remeasure and save the width.
  inline void resizeWidth() {
    m_rect.w = expand.x ? m_bounds.x : measureWidth();
  }

  // Remeasure and save the height.
  inline void resizeHeight() {
    m_rect.h = expand.y ? m_bounds.y : measureHeight();
  }

  // Remeasure and save the width and height.
  inline void resize() {
    resizeWidth();
    resizeHeight();
  }

  // Remeasure and save the size for the x-axis (width) or y-axis (height).
  inline void resize(Axis axis) {
    switch (axis) {
    case Axis::X: resizeWidth(); break;
    case Axis::Y: resizeHeight(); break;
    }
  }
};
} // namespace katzen
