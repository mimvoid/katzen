#pragma once
#include <raylib.h>
#include <climits>
#include <glm/ext/scalar_common.hpp>
#include <glm/ext/vector_bool2.hpp>
#include <glm/ext/vector_float2.hpp>
#include "../core/Bounds.hpp"
#include "../core/Dctx.hpp"
#include "../core/Edges.hpp"
#include "../core/Gctx.hpp"

namespace katzen {
/**
 * A basic widget for a retained mode GUI library.
 */
struct Widget {
  // Container widgets are allowed access to Widget's internals to query and
  // modify their children with less overhead.
  friend struct Box;

  Edges padding{0, 0, 0, 0};
  glm::bvec2 expand{false, false};

  virtual ~Widget() = default;

  // Get a rectangle with the widget's retained position and size.
  constexpr Rect rect() const { return m_rect; }

  /************/
  /* Position */
  /************/

  // Get the retained x-coordinate.
  constexpr float x() const { return m_rect.x; }

  // Get the retained y-coordinate.
  constexpr float y() const { return m_rect.y; }

  // Get the retained position.
  constexpr glm::vec2 position() const { return {m_rect.x, m_rect.y}; };

  /********/
  /* Size */
  /********/

  // Get the retained width.
  constexpr float width() const { return m_rect.w; }

  // Get the retained height.
  constexpr float height() const { return m_rect.h; }

  // Get the size on the x-axis (width) or y-axis (height).
  constexpr float size(Axis axis) const { return m_rect.size(axis); }

  // Remeasure and save the width.
  inline void resizeWidth() {
    m_rect.w = expand.x ? maxWidth() : measureWidth();
  }

  // Remeasure and save the height.
  inline void resizeHeight() {
    m_rect.h = expand.y ? maxHeight() : measureHeight();
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

  /**********/
  /* Bounds */
  /**********/

  constexpr unsigned int minWidth() const { return m_bounds.min.x; }
  constexpr unsigned int minHeight() const { return m_bounds.min.y; }

  constexpr unsigned int minSize(Axis axis) const {
    switch (axis) {
    case Axis::X: return minWidth();
    case Axis::Y: return minHeight();
    }
  }

  constexpr void setMinWidth(unsigned int value) { m_bounds.min.x = value; }
  constexpr void setMinHeight(unsigned int value) { m_bounds.min.y = value; }

  constexpr void setMinSize(unsigned int width, unsigned int height) {
    setMinWidth(width);
    setMinHeight(height);
  }

  constexpr unsigned int maxWidth() const {
    return glm::clamp(m_externalBounds.x, m_bounds.min.x, m_bounds.max.x);
  }
  constexpr unsigned int maxHeight() const {
    return glm::clamp(m_externalBounds.y, m_bounds.min.y, m_bounds.max.y);
  }

  constexpr unsigned int maxSize(Axis axis) const {
    switch (axis) {
    case Axis::X: return maxWidth();
    case Axis::Y: return maxHeight();
    }
  }

  constexpr void setMaxWidth(unsigned int value) { m_bounds.max.x = value; }
  constexpr void setMaxHeight(unsigned int value) { m_bounds.max.y = value; }

  constexpr void setMaxSize(unsigned int width, unsigned int height) {
    setMaxWidth(width);
    setMaxHeight(height);
  }

  constexpr bool expands(Axis axis) const {
    switch (axis) {
    case Axis::X: return expand.x;
    case Axis::Y: return expand.y;
    }
  }

  /***********/
  /* Padding */
  /***********/

  constexpr void pad(Edges newPadding) { padding = newPadding; }

  constexpr void pad(int top, int right, int bottom, int left) {
    padding = {top, right, bottom, left};
  }

  constexpr void pad(int top, int x, int bottom) {
    padding.set(top, x, bottom);
  }

  constexpr void pad(int y, int x) { padding.set(y, x); }
  constexpr void pad(int value) { padding.set(value); }

  /**********/
  /* Render */
  /**********/

  // Resize and reposition the widget and its children, if any.
  virtual void repaint(Gctx g);

  // Render the widget on the screen at its retained position.
  virtual void draw(Dctx &d) = 0;

protected:
  Rect m_rect{0, 0, 0, 0};

  // Minimum and maximum sizes intrinsic to the Widget.
  Bounds m_bounds{{0, 0}, {UINT_MAX, UINT_MAX}};

  // Maximum sizes that may be overridden by repaints.
  glm::uvec2 m_externalBounds{GetRenderWidth(), GetRenderHeight()};

  // Change the retained position.
  constexpr void reposition(glm::vec2 p) {
    m_rect.x = p.x;
    m_rect.y = p.y;
  }

  constexpr void reposition(Gctx g) {
    m_rect.x = g.x;
    m_rect.y = g.y;
  }

  constexpr void setExternalBounds(Gctx g) {
    m_externalBounds.x = g.w;
    m_externalBounds.y = g.h;
  }

  // Recalculate and return the size on the x-axis (width) or y-axis (height).
  virtual float measure(Axis axis) const;

  // Recalculate and return the width.
  inline float measureWidth() const { return measure(Axis::X); }

  // Recalculate and return the height.
  inline float measureHeight() const { return measure(Axis::Y); }

  constexpr float clampSize(float size, Axis axis) const {
    return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
  }
};
} // namespace katzen
