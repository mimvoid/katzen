#pragma once
#include <raylib.h>
#include <glm/ext/scalar_common.hpp>
#include <glm/ext/vector_bool2.hpp>
#include <glm/ext/vector_float2.hpp>
#include <memory>
#include "../core/Bounds.hpp"
#include "../core/Edges.hpp"
#include "../core/Gctx.hpp"
#include "../core/vec.hpp"

#define KATZEN_DEBUG

namespace katzen::widgets {
/**
 * A basic widget for a retained mode GUI library.
 */
struct Widget {
  Edges padding;
  glm::bvec2 expand;

  // Minimum and maximum sizes intrinsic to the Widget.
  Bounds bounds;

  // Maximum sizes that may be overridden by repaints.
  glm::uvec2 externalBounds;

  Widget();
  virtual ~Widget() {}

  /** A rectangle with the retained position and size. */
  constexpr Rect rect() const { return _box; }

  /************/
  /* Position */
  /************/

  // The retained x-coordinate.
  constexpr float x() const { return _box.x; }

  // The retained y-coordinate.
  constexpr float y() const { return _box.y; }

  // The retained position.
  constexpr glm::vec2 position() const { return {_box.x, _box.y}; };

  // Change the retained position.
  constexpr void position(glm::vec2 p) {
    _box.x = p.x;
    _box.y = p.y;
  }

  constexpr void position(Gctx g) {
    _box.x = g.x;
    _box.y = g.y;
  }

  /********/
  /* Size */
  /********/

  // The size on the x-axis (width) or y-axis (height).
  constexpr float size(Axis axis) const { return _box.size(axis); }

  // The retained width.
  constexpr float width() const { return _box.w; }

  // The retained height.
  constexpr float height() const { return _box.h; }

  // Remeasure and save the width.
  constexpr void updateWidth() {
    _box.w = expand.x ? maxWidth() : measureWidth();
  }

  // Remeasure and save the height.
  constexpr void updateHeight() {
    _box.h = expand.y ? maxHeight() : measureHeight();
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

  virtual void repaint(Gctx g);

  // Render the widget on the screen at its retained position.
  constexpr void draw() {
#if defined(KATZEN_DEBUG)
    DrawRectangleLinesEx(rlRectangle(rect()), 1, RED);
#endif

    draw(position());
  }

  /**
   * A utility function to render the widget on the screen at a
   * given position.
   *
   * This is meant for widgets to draw the widgets they inherited from.
   */
  virtual void draw(glm::vec2 p) = 0;

protected:
  Rect _box;

  // Recalculate and return the size on the x-axis (width) or y-axis (height).
  virtual float measureSize(Axis axis) const {
    return glm::clamp(
        padding.get(axis), (int)minSize(axis), (int)maxSize(axis));
  }

  // Recalculate and return the width.
  constexpr float measureWidth() const { return measureSize(Axis::X); }

  // Recalculate and return the height.
  constexpr float measureHeight() const { return measureSize(Axis::Y); }
};

template <typename T, typename... Args>
std::unique_ptr<T> mkWidget(Args &&...args) {
  return std::make_unique<T>(args...);
}
} // namespace katzen::widgets
