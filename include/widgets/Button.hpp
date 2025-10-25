#pragma once
#include <cassert>
#include <functional>
#include "../parts/Reactive.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class ChildT>
struct Button : Widget, Reactive {
  using OnPress = std::function<void()>;

  struct Builder : WidgetBuilder {
    constexpr Builder() = default;

    Builder &onPress(OnPress callback) {
      m_onPress = callback;
      return *this;
    }

    Button build(ChildT &&child) const {
      Button button{child, m_onPress};
      setWidgetProps(button);
      return button;
    }

  private:
    OnPress m_onPress{};
  };

  ChildT child;
  OnPress onPress;

  Button(ChildT &&child, OnPress onPress = OnPress())
      : child(std::move(child)), onPress(onPress) {
    padding.set(8);
  }

  void repaint(Gctx g) override {
    setBounds(g);
    reposition(g);

    g.pad(padding);
    child.repaint(g);

    resize();
  }

  void draw(Dctx &d) override {
    const Rectangle box = m_rect;

    if (updateState(d, box) && onPress) {
      onPress();
    }

    DrawRectangleRec(box, d.colors.base);
    if (d.borderWidth != 0) {
      DrawRectangleLinesEx(box, d.borderWidth, d.colors.border);
    }

    child.draw(d);
  }

protected:
  float measure(Axis axis) const override {
    const float size = child.size(axis) + padding.getSum(axis);
    return clampSize(size, axis);
  }
};
} // namespace katzen
