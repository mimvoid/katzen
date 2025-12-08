#ifndef KATZE_CTX_GCTX_HPP
#define KATZE_CTX_GCTX_HPP

#include "../core/Axis.hpp"
#include "../core/Edges.hpp"
// #include "../theme/FontStyle.hpp"

namespace katze {
/**
 * A graphics context that provides necessary information for resizing widgets.
 */
struct Gctx {
  // const FontStyle &font{};
  float w{0.0f};
  float h{0.0f};

  // Gctx(const FontStyle &font) : font(font) {}

  constexpr void shrink(FEdges padding) {
    w -= padding.getX();
    h -= padding.getY();
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

#endif // !KATZE_CTX_GCTX_HPP
