#pragma once
#include <raylib.h>

namespace katzen {
enum class State { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Color border;
  Color base;
  Color text;
};

/**
 * A drawing context, which keeps track of simple theme variables for fewer
 * lookups, and stores a widget state that can be passed to children.
 */
struct Dctx {
  const unsigned int borderWidth;
  const unsigned int borderRadius;
  const unsigned int iconSize;

  StateColors colors;
  State state = State::NORMAL;
  int cursor = MOUSE_CURSOR_DEFAULT;
};
} // namespace katzen
