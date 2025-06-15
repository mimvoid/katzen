#pragma once
#include <functional>
#include <glm/ext/scalar_common.hpp>
#include "../components/Reactive.hpp"
#include "Widget.hpp"

namespace katzen {
struct Checkbox : Widget, Reactive {
  bool checked;
  std::function<void(bool)> callback;

  Checkbox(
      float scale = 1.0f,
      bool checked = false,
      std::function<void(bool)> callback = std::function<void(bool)>(),
      std::function<void(Checkbox &)> setup = std::function<void(Checkbox &)>())
      : checked(checked), callback(callback), m_scale(scale) {
    if (setup) setup(*this);
  }

  constexpr float scale() const { return m_scale; }
  constexpr void scale(float scale) { m_scale = glm::max(0.1f, scale); }

  void draw(glm::vec2 p) override;

protected:
  unsigned int m_borderWidth =
      theme::getProperty(theme::UIntProp::BORDER_WIDTH);

  float measureSize(Axis axis) const override;

private:
  float m_scale;
};
} // namespace katzen
