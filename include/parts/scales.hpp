#pragma once

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
