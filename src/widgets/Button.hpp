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

  void draw() override {
    Widget::draw();
    const Rectangle box = rlRectangle(rect());

    if (updateState(box) && callback) {
      callback();
    }

    DrawRectangleRec(box, m_colors.base);
    if (m_borderWidth != 0) {
      DrawRectangleLinesEx(box, m_borderWidth, m_colors.border);
    }

    child.draw();
  }

protected:
  unsigned int m_borderWidth =
      theme::getProperty(theme::UIntProp::BORDER_WIDTH);

  float measureSize(Axis axis) const override {
    const float size =
        child.size(axis) + padding.get(axis) + (2 * m_borderWidth);
    return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
  }
};
} // namespace katzen
