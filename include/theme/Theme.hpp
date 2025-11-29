#pragma once
#include "../core/State.hpp"

namespace katzen {
/**
 * Settings to theme katzen widgets.
 *
 * NOTE: borderRadius is currently unimplemented
 */
struct Theme {
  StateColors normal{
      {242, 160, 164, 255}, {250, 223, 200, 255}, {39, 39, 42, 255}};

  StateColors disabled{
      {217, 141, 150, 255}, {235, 192, 180, 255}, {57, 57, 60, 255}};

  StateColors focus{
      {248, 149, 155, 255}, {250, 214, 190, 255}, {39, 39, 42, 255}};

  StateColors active{
      {54, 47, 64, 255}, {213, 132, 134, 255}, {252, 229, 233, 255}};

  Color backgroundColor{255, 245, 225, 255};

  uint8_t borderWidth{2};
  uint8_t borderRadius{0};
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
} // namespace katzen
