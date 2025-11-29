#pragma once
#include <functional>
#include "Widget.hpp"
#include "WidgetBuilder.hpp"
#include "../parts/Bin.hpp"
#include "../parts/Reactive.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class ChildT>
struct Button : Widget, Reactive, Bin<ChildT> {
  using OnPress = std::function<void()>;
  struct Builder;

  OnPress onPress;

  Button(ChildT &&child, OnPress onPress = OnPress())
      : Bin<ChildT>(std::move(child)), onPress(onPress) {
    padding.set(8);
  }

  void repaint(Gctx &g) override {
    setBounds(g);
    reposition(g);

    g.pad(padding);
    this->child.repaint(g);

    resize();
  }

  void translate(float dx, float dy) override {
    Widget::translate(dx, dy);
    this->child.translate(dx, dy);
  }

  void draw(Dctx &d) override {
    const Rectangle box = (Rectangle)m_rect;

    if (updateState(d, box) && onPress) {
      onPress();
    }

    DrawRectangleRec(box, d.colors().base);
    if (d.theme.borderWidth != 0) {
      DrawRectangleLinesEx(box, d.theme.borderWidth, d.colors().border);
    }

    this->child.draw(d);
  }

protected:
  float measure(Axis axis) const override {
    const float size = this->child.size(axis) + padding.getSum(axis);
    return clampSize(size, axis);
  }

public:
  struct Builder : WidgetBuilder<Builder>, BinBuilder<ChildT> {
    constexpr Builder() { this->m_padding.set(8); }

    constexpr Builder &enabled(bool value) {
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

      this->setWidgetProps(button);
      return button;
    }

  private:
    OnPress m_onPress{};
    bool m_enabled{true};
  };
};
} // namespace katzen
