#pragma once
#include <functional>
#include <type_traits>
#include <utility>
#include "../components/Reactive.hpp"
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class T>
struct Button : Widget, Reactive {
  static_assert(std::is_base_of_v<Widget, T>,
                "A katzen Button must have a child derived from Widget");

  T child;
  std::function<void()> callback;

  Button(T &&child, std::function<void()> callback = std::function<void()>())
      : child(std::move(child)), callback(callback) {
    padding.set(8);
  }

  template <typename... Args>
  Button(std::function<void()> callback, Args &&...args)
      : child(std::forward(args...)), callback(callback) {
    padding.set(8);
  }

  void repaint(Gctx g) override {
    setExternalBounds(g);
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
    return clampSize(size, axis);
  }
};
} // namespace katzen
