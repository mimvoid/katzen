#include <functional>
#include "../components/Container.hpp"
#include "../core/Align.hpp"
#include "Widget.hpp"

namespace katzen::widgets {
/**
 * A widget that contains other widgets.
 * It handles their sizes and alignments.
 */
struct Box : Widget, Container {
  int spacing;
  Axis direction;
  Align halign, valign;

  Box(std::function<void(const Box &)> setup,
      int spacing,
      Axis direction,
      Align halign,
      Align valign)
      : Box(spacing, direction, halign, valign) {
    setup(*this);
  }

  Box(int spacing, Axis direction, Align halign, Align valign)
      : spacing(spacing),
        direction(direction),
        halign(halign),
        valign(valign) {}

  Box() : Box(0, Axis::X, Align::START, Align::START) {}

  constexpr Align align(Axis axis) const {
    switch (axis) {
    case Axis::X: return halign;
    case Axis::Y: return valign;
    }
  }

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureChildren(Axis axis);
  float childrenSize(Axis axis) const;
  float measureSize(Axis a) const override;
};
} // namespace katzen::widgets
