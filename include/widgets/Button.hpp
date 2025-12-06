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
  using OnPress = std::function<void(Button &self)>;
  struct Builder;

  OnPress onPress{};

  Button() : Widget(Edges(8)) {}

  Button(ChildT &&child, OnPress onPress = {})
    : Widget(Edges(8)), Bin<ChildT>(std::move(child)), onPress(onPress) {}

  Button(ChildT &&child, std::function<void()> onPress)
    : Widget(Edges(8)),
      Bin<ChildT>(std::move(child)),
      onPress([onPress]([[maybe_unused]] auto &self) { onPress(); }) {}

  void resize(Gctx g) override {
    g.pad(padding);
    this->child.resize(g);

    m_rect.w = this->child.width() + padding.getX();
    m_rect.h = this->child.height() + padding.getY();
  }

  void reposition(Vec2 position) override {
    Widget::reposition(position);
    this->child.reposition(
      Vec2{position.x + padding.left, position.y + padding.top}
    );
  }

  void draw(Dctx &d) override {
    const Rectangle rec = (Rectangle)m_rect;

    if (updateState(d, rec) && onPress) {
      onPress(*this);
    }

    DrawRectangleRec(rec, (Color)d.colors().base);
    if (d.theme.borderWidth != 0) {
      DrawRectangleLinesEx(rec, d.theme.borderWidth, (Color)d.colors().border);
    }

    this->child.draw(d);
  }

public:
  struct Builder : WidgetBuilder<Builder>, BinBuilder<ChildT, Builder> {
    constexpr Builder() { this->m_padding.set(8); }

    constexpr Builder &enabled(bool value) {
      m_enabled = value;
      return *this;
    }

    Builder &onPress(OnPress callback) {
      m_onPress = callback;
      return *this;
    }
    Builder &onPress(std::function<void()> callback) {
      m_onPress = [callback]([[maybe_unused]] auto &self) { callback(); };
      return *this;
    }

    Button build() {
      Button button(std::move(this->m_child), m_onPress);
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
Button(ChildT &&, std::function<void(Button<ChildT> &)>) -> Button<ChildT>;

template <class ChildT>
Button(ChildT &&, std::function<void()>) -> Button<ChildT>;
} // namespace katzen
