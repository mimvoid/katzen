#pragma once
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
  struct Builder;

  OnPress onPress;

  Button(ChildT &&child, OnPress onPress = OnPress())
      : Bin<ChildT>(std::move(child)), onPress(onPress) {
    padding.set(8);
  }

  void resize(Gctx g) override {
    g.pad(padding);
    this->child.resize(g);

    m_rect.w = this->child.width() + padding.getX();
    m_rect.h = this->child.height() + padding.getY();
  }

  void reposition(Vec2 position) override {
    Widget::reposition(position);
    this->child.reposition(
        Vec2{position.x + padding.left, position.y + padding.top});
  }

  void draw(Dctx &d) override {
    const Rectangle rec = (Rectangle)m_rect;

    if (updateState(d, rec) && onPress) {
      onPress();
    }

    DrawRectangleRec(rec, (Color)d.colors().base);
    if (d.theme.borderWidth != 0) {
      DrawRectangleLinesEx(rec, d.theme.borderWidth, (Color)d.colors().border);
    }

    this->child.draw(d);
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
      this->hasChild();
      Button button(std::move(*this->m_child), m_onPress);
      this->m_child.reset();

      button.enabled = m_enabled;
      this->setWidgetProps(button);
      return button;
    }

  private:
    OnPress m_onPress{};
    bool m_enabled{true};
  };
};

template <class ChildT>
Button(ChildT &&, std::function<void()>) -> Button<ChildT>;
} // namespace katzen
