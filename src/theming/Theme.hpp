#pragma once
#include "../core/Dctx.hpp"
#include <raylib.h>
#include <cstdint>

namespace katzen::theme {
struct Theme {
  uint8_t borderWidth;
  uint8_t borderRadius;
  uint8_t iconSize;
  Color backgroundColor;

  StateColors normal;
  StateColors disabled;
  StateColors focus;
  StateColors active;
};
} // namespace katzen::theme
