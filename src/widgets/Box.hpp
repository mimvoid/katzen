#include <functional>
#include <memory>
#include <vector>
#include "../core/Align.hpp"
#include "Widget.hpp"

namespace katzen::widgets {
/**
 * A widget that contains other widgets.
 * It handles their sizes and alignments.
 */
struct Box : Widget {
  int spacing;
  Axis direction;
  Align halign, valign;
  std::vector<std::unique_ptr<Widget>> children;

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
        valign(valign),
        children{} {}

  Box() : Box(0, Axis::X, Align::START, Align::START) {}

  constexpr Align align(Axis axis) const {
    switch (axis) {
    case Axis::X: return halign;
    case Axis::Y: return valign;
    }
  }

  template <typename T>
  void push(T &&child) {
    children.push_back(std::make_unique<T>(std::move(child)));
  }

  template <typename T, typename... Args>
  void emplace(Args &&...args) {
    children.emplace_back(std::make_unique<T>(args...));
  }

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureChildren(Axis axis);
  float childrenSize(Axis axis) const;
  float measureSize(Axis a) const override;
};
} // namespace katzen::widgets
