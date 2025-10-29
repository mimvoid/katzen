#pragma once
#include <functional>
#include "../parts/Reactive.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
struct Slider : Widget, Reactive {
  using OnValueChange = std::function<void(float)>;

  struct Builder : WidgetBuilder<Builder> {
    constexpr Builder &value(float value) {
      m_initValue = std::clamp(value, 0.0f, 1.0f);
      return *this;
    }

    Builder &onValueChange(OnValueChange callback) {
      m_onValueChange = callback;
      return *this;
    }

    Slider build() const {
      Slider slider(m_initValue, m_onValueChange);
      setWidgetProps(slider);
      return slider;
    }

  private:
    float m_initValue{0.0f};
    OnValueChange m_onValueChange{};
  };

  Axis direction{Axis::X};
  OnValueChange onValueChange{};

  Slider(float initialValue, OnValueChange onValueChange = OnValueChange())
      : onValueChange(onValueChange) {
    setValue(initialValue);
  }

  constexpr float value() const { return m_value; }
  constexpr void setValue(float value) {
    m_value = std::clamp(value, 0.0f, 1.0f);
  }

  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;

private:
  float m_value{0.0f};
  float m_sizeScale{1.0f};
  bool m_dragging{false};
};
} // namespace katzen
