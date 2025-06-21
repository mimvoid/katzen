#include "themer.hpp"

namespace katzen::theme {
static Theme theme{
    2,
    0,
    1,
    {255, 245, 225, 255},
    {{242, 160, 164, 255}, {250, 223, 200, 255}, {39, 39, 42, 255}},
    {{217, 141, 150, 255}, {235, 192, 180, 255}, {57, 57, 60, 255}},
    {{248, 149, 155, 255}, {250, 214, 190, 255}, {39, 39, 42, 255}},
    {{54, 47, 64, 255}, {213, 132, 134, 255}, {252, 229, 233, 255}}};

Theme &getTheme() { return theme; }
Theme &setTheme(Theme newTheme) {
  theme = newTheme;
  return theme;
}

StateColors &getStateColors(State state) {
  switch (state) {
  case State::DISABLED: return theme.disabled;
  case State::FOCUS:    return theme.focus;
  case State::ACTIVE:   return theme.active;
  default:              return theme.normal;
  }
}
} // namespace katzen::theme
