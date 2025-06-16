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
#include "../core/vec.hpp"

namespace katzen {
/**
 * A basic widget for a retained mode GUI library.
 */
struct Widget {
  friend struct Box;

  Edges padding{0, 0, 0, 0};
  glm::bvec2 expand{false, false};

  // Minimum and maximum sizes intrinsic to the Widget.
  Bounds bounds{{0, 0}, {UINT_MAX, UINT_MAX}};

  virtual ~Widget() = default;

  /** A rectangle with the retained position and size. */
  constexpr Rect rect() const { return m_box; }

  /************/
  /* Position */
  /************/

  // The retained x-coordinate.
  constexpr float x() const { return m_box.x; }

  // The retained y-coordinate.
  constexpr float y() const { return m_box.y; }

  // The retained position.
  constexpr glm::vec2 position() const { return {m_box.x, m_box.y}; };

  /********/
  /* Size */
  /********/

  // The size on the x-axis (width) or y-axis (height).
  constexpr float size(Axis axis) const { return m_box.size(axis); }

  // The retained width.
  constexpr float width() const { return m_box.w; }

  // The retained height.
  constexpr float height() const { return m_box.h; }

  // Remeasure and save the width.
  constexpr void updateWidth() {
    m_box.w = expand.x ? maxWidth() : measureWidth();
  }

  // Remeasure and save the height.
  constexpr void updateHeight() {
    m_box.h = expand.y ? maxHeight() : measureHeight();
  }

  constexpr void updateSize() {
    updateWidth();
    updateHeight();
  }

  // Remeasure and save the size for the x-axis (width) or y-axis (height).
  constexpr void updateSize(Axis axis) {
    switch (axis) {
    case Axis::X: updateWidth(); break;
    case Axis::Y: updateHeight(); break;
    }
  }

  /**********/
  /* Bounds */
  /**********/

  constexpr unsigned int minSize(Axis axis) const {
    return get(bounds.min, axis);
  }

  constexpr unsigned int maxWidth() const {
    return glm::clamp(externalBounds.x, bounds.min.x, bounds.max.x);
  }

  constexpr unsigned int maxHeight() const {
    return glm::clamp(externalBounds.y, bounds.min.y, bounds.max.y);
  }

  constexpr unsigned int maxSize(Axis axis) const {
    switch (axis) {
    case Axis::X: return maxWidth();
    case Axis::Y: return maxHeight();
    }
  }

  /**********/
  /* Render */
  /**********/

  virtual void repaint(Gctx g) {
    setExternalBounds(g);
    position(g);
    updateSize();
  }

  // Render the widget on the screen at its retained position.
  virtual void draw(Dctx &d) = 0;

protected:
  // Maximum sizes that may be overridden by repaints.
  glm::uvec2 externalBounds{GetRenderWidth(), GetRenderHeight()};
  Rect m_box;

  // Change the retained position.
  constexpr void position(glm::vec2 p) {
    m_box.x = p.x;
    m_box.y = p.y;
  }

  constexpr void position(Gctx g) {
    m_box.x = g.x;
    m_box.y = g.y;
  }

  constexpr void setExternalBounds(Gctx g) {
    externalBounds.x = g.w;
    externalBounds.y = g.h;
  }

  // Recalculate and return the size on the x-axis (width) or y-axis (height).
  virtual float measureSize(Axis axis) const {
    return glm::clamp(
        padding.get(axis), (int)minSize(axis), (int)maxSize(axis));
  }

  // Recalculate and return the width.
  constexpr float measureWidth() const { return measureSize(Axis::X); }

  // Recalculate and return the height.
  constexpr float measureHeight() const { return measureSize(Axis::Y); }

  constexpr float clampSize(float size, Axis axis) const {
    return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
  }
};
} // namespace katzen
