#pragma once
#include <cassert>
#include <functional>
#include "../parts/Bin.hpp"
#include "../parts/Reactive.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class ChildT>
struct Button : Widget, Reactive, Bin<ChildT> {
  using OnPress = std::function<void()>;

  struct Builder : WidgetBuilder, BinBuilder<ChildT> {
    Builder() { m_padding.set(8); }

    Builder &enabled(bool value) {
      m_enabled = value;
      return *this;
    }

    Builder &onPress(OnPress callback) {
      m_onPress = callback;
      return *this;
    }

    Builder &child(ChildT &&child) {
      this->m_child = std::move(child);
      return *this;
    }

    template <typename... Args>
    Builder &emplaceChild(Args &&...args) {
      this->m_child.emplace(std::forward<Args>(args)...);
      return *this;
    }

    Button build() {
      this->checkChild();
      Button button(std::move(*this->m_child), m_onPress);
      this->m_child.reset();

      if (!m_enabled) {
        button.disable();
      }

      setWidgetProps(button);
      return button;
    }

  private:
    OnPress m_onPress{};
    bool m_enabled{true};
  };

  OnPress onPress;

  Button(ChildT &&child, OnPress onPress = OnPress())
      : Bin<ChildT>(std::move(child)), onPress(onPress) {
    padding.set(8);
  }

  void repaint(Gctx g) override {
    setBounds(g);
    reposition(g);

    g.pad(padding);
    this->child.repaint(g);

    resize();
  }

  void draw(Dctx &d) override {
    const Rectangle box = (Rectangle)m_rect;

    if (updateState(d, box) && onPress) {
      onPress();
    }

    DrawRectangleRec(box, d.colors.base);
    if (d.borderWidth != 0) {
      DrawRectangleLinesEx(box, d.borderWidth, d.colors.border);
    }

    this->child.draw(d);
  }

protected:
  float measure(Axis axis) const override {
    const float size = this->child.size(axis) + padding.getSum(axis);
    return clampSize(size, axis);
  }
};
} // namespace katzen
