#pragma once
#include <functional>
#include "../components/Reactive.hpp"
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class T>
struct Button : Widget, Reactive {
  T child;
  std::function<void()> callback;

  Button(T &&child, std::function<void()> callback = std::function<void()>())
      : child(std::move(child)), callback(callback) {
    padding.set(8);
  }

  void repaint(Gctx g) override {
    externalBounds.x = g.w;
    externalBounds.y = g.h;

    position(g);

    g.pad(padding);
    child.repaint(g);

    updateSize();
  }

  void draw(Dctx &d) override {
    const Rectangle box = m_box;

    if (updateState(d, box) && callback) {
      callback();
    }

    DrawRectangleRec(box, d.colors.base);
    if (d.borderWidth != 0) {
      DrawRectangleLinesEx(box, d.borderWidth, d.colors.border);
    }

    child.draw(d);
  }

protected:
  float measureSize(Axis axis) const override {
    const float size = child.size(axis) + padding.get(axis);
    return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
  }
};
} // namespace katzen
