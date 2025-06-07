#pragma once

namespace katzen {
enum class Align { START, CENTER, END };

/**
 * Calculate how much to offset a child according to how it is align with the
 * parent.
 *
 * Any given size that is negative is considered 0.
 *
 * @param parentSize The size of the parent
 * @param childSize The size of the child
 * @param The alignment of the child in respect to the parent
 * @return How much the offset the child
 */
constexpr float offset(float parentSize, float childSize, Align align) {
  if (align == Align::START) {
    // There would be no offset needed regardless of size
    return 0.0f;
  }

  if (parentSize < 0.0f)
    parentSize = 0.0f;

  if (childSize < 0.0f)
    childSize = 0.0f;

  const float sizeDiff = parentSize - childSize;
  return (align == Align::CENTER) ? (sizeDiff / 2.0f) : sizeDiff;
}
} // namespace katzen
