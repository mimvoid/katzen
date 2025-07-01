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
template <class ChildWidgetT>
struct Button : Widget, Reactive {
  static_assert(std::is_base_of_v<Widget, ChildWidgetT>,
                "A katzen Button must have a child derived from Widget");
  using value_type = ChildWidgetT;

  ChildWidgetT child;
  std::function<void()> callback;

  Button(ChildWidgetT &&child,
         std::function<void()> callback = std::function<void()>())
      : child(std::move(child)), callback(callback) {
    padding.set(8);
  }

  template <typename... Args>
  Button(std::function<void()> callback, Args &&...args)
      : child(std::forward<Args>(args)...), callback(callback) {
    padding.set(8);
  }

  void repaint(Gctx g) override {
    setExternalBounds(g);
    reposition(g);

    g.pad(padding);
    child.repaint(g);

    resize();
  }

  void draw(Dctx &d) override {
    const Rectangle box = m_rect;

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
  float measure(Axis axis) const override {
    const float size = child.size(axis) + padding.get(axis);
    return clampSize(size, axis);
  }
};
} // namespace katzen
