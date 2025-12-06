#pragma once
#include "../core/Axis.hpp"
#include "../core/Edges.hpp"
#include "../theme/FontStyle.hpp"

namespace katzen {
/**
 * A graphics context that provides necessary information for resizing widgets.
 */
struct Gctx {
  const FontStyle &font{};
  float w{0.0f};
  float h{0.0f};

  Gctx(const FontStyle &font) : font(font) { reset(); }
  Gctx(const FontStyle &font, Edges padding) : font(font) { reset(padding); }

  void reset() {
    w = GetRenderWidth();
    h = GetRenderHeight();
  }

  void reset(Edges padding) {
    w = GetRenderWidth() - padding.left - padding.right;
    h = GetRenderHeight() - padding.top - padding.bottom;
  }

  constexpr void pad(Edges padding) {
    w -= padding.left + padding.right;
    h -= padding.top + padding.bottom;
  }

  constexpr float size(Axis axis) const { return (axis == Axis::X) ? w : h; }

  constexpr void setSize(Axis axis, float value) {
    switch (axis) {
    case Axis::X: w = value; break;
    case Axis::Y: h = value; break;
    }
  }

  constexpr float clampWidth(float width) const {
    if (width < 0.0f) return 0.0f;
    return width <= w ? width : w;
  }

  constexpr float clampHeight(float height) const {
    if (height < 0.0f) return 0.0f;
    return height <= h ? height : h;
  }

  constexpr float clampSize(float value, Axis axis) const {
    return (axis == Axis::X) ? clampWidth(value) : clampHeight(value);
  }
};
} // namespace katzen
