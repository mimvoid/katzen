#pragma once
#include <functional>
#include "../parts/Reactive.hpp"
#include "Widget.hpp"
#include "WidgetBuilder.hpp"

namespace katzen {
struct Slider : Widget, Reactive {
  using OnValueChange = std::function<void(float)>;
  struct Builder;

  Axis direction{Axis::X};
  OnValueChange onValueChange{};

  Slider() = default;

  Slider(float initialValue, OnValueChange onValueChange = OnValueChange())
      : onValueChange(onValueChange) {
    setValue(initialValue);
  }

  constexpr float value() const { return m_value; }
  constexpr void setValue(float value) {
    if (value < 0.0f)
      m_value = 0.0f;
    else
      m_value = value > 1.0f ? 1.0f : value;
  }

  void resize(Gctx g) override;
  void draw(Dctx &d) override;

private:
  float m_value{0.0f};
  float m_sizeScale{1.0f};
  bool m_dragging{false};

public:
  struct Builder : WidgetBuilder<Builder> {
    constexpr Builder &value(float value) {
      if (value < 0.0f)
        m_initValue = 0.0f;
      else
        m_initValue = value > 1.0f ? 1.0f : value;
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
};
} // namespace katzen
