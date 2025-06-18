#pragma once
#include <functional>
#include <glm/ext/scalar_common.hpp>
#include "../components/Reactive.hpp"
#include "Widget.hpp"

namespace katzen {
struct Slider : Widget, Reactive {
  Axis direction;
  std::function<void(float)> callback;

  Slider(float initialValue,
         Axis direction = Axis::X,
         float sizeScale = 1.0f,
         std::function<void(float)> callback = std::function<void(float)>(),
         std::function<void(Slider &)> setup = std::function<void(Slider &)>());

  constexpr float value() const { return m_value; }
  constexpr void value(float newValue) {
    m_value = glm::clamp(newValue, 0.0f, 1.0f);
  }

  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;

private:
  float m_value;
  float m_sizeScale = 1.0f;
  bool m_dragging = false;
};
} // namespace katzen
