#pragma once
#include <functional>
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
      : checked(checked), callback(callback) {
    setScale(scale);
    if (setup) setup(*this);
  }

  constexpr float getScale() const { return m_scale; }
  constexpr void setScale(float scale) { m_scale = std::max(0.1f, scale); }

  void draw(Dctx &d) override;

protected:
  float measure(Axis axis) const override;

private:
  float m_scale;
};
} // namespace katzen
