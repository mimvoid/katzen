#pragma once
#include "../core/Dctx.hpp"
#include <raylib.h>

namespace katzen::theme {
struct Theme {
  unsigned int borderWidth;
  unsigned int borderRadius;
  unsigned int iconSize;
  Color backgroundColor;

  StateColors normal;
  StateColors disabled;
  StateColors focus;
  StateColors active;
};
} // namespace katzen::theme
