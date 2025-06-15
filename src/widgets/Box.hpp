#include <functional>
#include "../components/Container.hpp"
#include "../core/Align.hpp"
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that contains other widgets.
 * It handles their sizes and alignments.
 */
struct Box : Widget, Container {
  int spacing;
  Axis direction;
  Align halign, valign;

  Box(int spacing = 0,
      Axis direction = Axis::X,
      Align halign = Align::START,
      Align valign = Align::START,
      std::function<void(Box &)> setup =
          std::function<void(Box &)>())
      : spacing(spacing), direction(direction), halign(halign), valign(valign) {
    if (setup) setup(*this);
  }

  constexpr Align align(Axis axis) const {
    switch (axis) {
    case Axis::X: return halign;
    case Axis::Y: return valign;
    }
  }

  void repaint(Gctx g) override;
  void draw(Dctx &d) override;

protected:
  float measureChildren(Axis axis);
  float childrenSize(Axis axis) const;
  float measureSize(Axis a) const override;
};
} // namespace katzen
