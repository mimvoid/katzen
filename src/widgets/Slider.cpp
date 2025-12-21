#include "widgets/Slider.hpp"
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
/**
 * Convert a value with a minimum and maximum limit to a scaled value for a
 * range of 0.0f to 1.0f.
 *
 * This function does not clip the value.
 * - If the unscaled value is less than its minimum limit, this returns a
 * negative number.
 * - If it's greater than its maximum limit, this returns a number greater
 * than 1.0f.
 */
constexpr float
toScaledValue(float unscaledValue, float unscaledMin, float unscaledMax) {
  const float range = unscaledMax - unscaledMin;
  return (unscaledValue - unscaledMin) / range;
}

/**
 * Convert a scaled value with a range of 0.0f to 1.0f to an unscaled value
 * with the given minimum and maximum limits.
 *
 * This function does not clip the value.
 * - If the scaled value is less than 0.0f, this returns a number less than the
 * unscaled minimum.
 * - If it's greater than 1.0f, this returns a number greater than greater than
 * the unscaled maximum.
 */
constexpr float
fromScaledValue(float scaledValue, float unscaledMin, float unscaledMax) {
  const float range = unscaledMax - unscaledMin;
  return (scaledValue * range) - unscaledMin;
}

void Slider::resize(Gctx g, FRect &rect) {
  const float troughThickness = m_sizeScale * g.font.size();
  const float dirSize = g.clampSize(troughThickness * 4, direction);
  const float flipSize = g.clampSize(troughThickness, !direction);

  rect.setSizes(direction, dirSize, flipSize);
}

void Slider::view(Dctx &d, FRect rect) {
  const bool pressReleased = updateState(d, rect);

  const float gap = d.root.theme.borderWidth * 2;
  SDL_FRect trough{
    rect.x + gap, rect.y + gap, rect.w - (2 * gap), rect.h - (2 * gap)
  };

  // Update the slider value
  if (enabled && d.mouse.valid && (d.root.focused == this || pressReleased)) {
    if (direction == Axis::X)
      setValue(toScaledValue(d.mouse.x, trough.x, trough.x + trough.w));
    else
      setValue(toScaledValue(d.mouse.y, trough.y, trough.y + trough.h));

    if (pressReleased) {
      d.root.messages.push_back(onValueUpdate);
    }
  }

  const SDL_FRect rec{rect.x, rect.y, rect.w, rect.h};
  const StateColors &colors = d.colors();

  // Draw the slider.
  d.root.renderer.setDrawColor(colors.base);
  SDL_RenderFillRect(d.root.renderer.data, &rec);

  d.root.renderer.setDrawColor(colors.border);
  if (d.root.theme.borderWidth != 0) {
    SDL_RenderRect(d.root.renderer.data, &rec);
  }

  // Draw the trough.
  if (m_value != 0.0f) {
    if (m_value != 1.0f) {
      if (direction == Axis::X) {
        trough.w *= m_value;
      } else {
        const float fullHeight = trough.h;
        trough.h *= m_value;
        trough.y += fullHeight - trough.h;
      }
    }

    SDL_RenderFillRect(d.root.renderer.data, &trough);
  }
}
} // namespace katze
