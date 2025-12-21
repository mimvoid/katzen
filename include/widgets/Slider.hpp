#ifndef KATZE_WIDGETS_SLIDER_HPP
#define KATZE_WIDGETS_SLIDER_HPP

#include "../Reactive.hpp"
#include "Widget.hpp"

namespace katze {
struct Slider : Widget, Reactive {
  Axis direction{Axis::X};
  uint32_t onValueUpdate{0};

  Slider() : Reactive(false, true) {}

  Slider(float initialValue, uint32_t onValueUpdate)
    : Reactive(true, true), onValueUpdate(onValueUpdate) {
    setValue(initialValue);
  }

  constexpr float value() const { return m_value; }
  constexpr void setValue(float value) {
    if (value <= 0.0f)
      m_value = 0.0f;
    else
      m_value = value > 1.0f ? 1.0f : value;
  }

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;

private:
  float m_value{0.0f};
  float m_sizeScale{1.0f};
};
} // namespace katze

#endif // !KATZE_WIDGETS_SLIDER_HPP
