#ifndef KATZE_THEME_HPP
#define KATZE_THEME_HPP

#include "core/State.hpp"

namespace katze {
/**
 * Settings to theme katze widgets.
 */
struct Theme {
  StateColors normal{{242, 160, 164}, {250, 223, 200}, {39, 39, 42}};
  StateColors disabled{{217, 141, 150}, {235, 192, 180}, {57, 57, 60}};
  StateColors focus{{248, 149, 155}, {250, 214, 190}, {39, 39, 42}};
  StateColors active{{54, 47, 64}, {213, 132, 134}, {252, 229, 233}};

  uint8_t borderWidth{2};
  uint8_t iconSize{1};

  constexpr const StateColors &stateColors(State state) const {
    switch (state) {
    case State::DISABLED: return disabled;
    case State::FOCUS:    return focus;
    case State::ACTIVE:   return active;
    default:              return normal;
    }
  }
};
} // namespace katze

#endif // !KATZE_THEME_HPP
