#pragma once
#include <functional>
#include "Widget.hpp"
#include "WidgetBuilder.hpp"
#include "parts/Reactive.hpp"

namespace katzen {
struct Checkbox : Widget, Reactive {
  using OnCheck = std::function<void(bool)>;
  struct Builder;

  bool checked{false};
  OnCheck onCheck{};

  Checkbox() = default;
  Checkbox(bool checked, OnCheck callback)
      : checked(checked), onCheck(callback) {}

  constexpr float scale() const { return m_scale; }
  constexpr void setScale(float scale) { m_scale = std::max(0.1f, scale); }

  void repaint(Gctx &g) override;
  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;

private:
  float m_scale{1.0f};
  float m_fontSize{1.0f};

public:
  struct Builder : WidgetBuilder<Builder> {
    constexpr Builder &checked(bool value) {
      m_checked = value;
      return *this;
    }

    constexpr Builder &scale(float value) {
      m_scale = value;
      return *this;
    }

    Builder &onCheck(OnCheck callback) {
      m_onCheck = callback;
      return *this;
    }

    Checkbox build() const {
      Checkbox checkbox(m_checked, m_onCheck);
      checkbox.setScale(m_scale);
      setWidgetProps(checkbox);
      return checkbox;
    }

  private:
    bool m_checked{false};
    float m_scale{1.0f};
    OnCheck m_onCheck{};
  };
};
} // namespace katzen
