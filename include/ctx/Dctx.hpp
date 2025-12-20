#ifndef KATZE_CTX_DCTX_HPP
#define KATZE_CTX_DCTX_HPP

#include "../Root.hpp"
#include "../core/State.hpp"
#include "../input/Cursor.hpp"
#include "../input/mouse.hpp"

struct SDL_Renderer;

namespace katze {
/**
 * A drawing context that provides theme settings and stores a widget state
 * that can be passed to children.
 */
struct Dctx {
  struct MouseInfo {
    bool valid{false}; // Whether the info applies to this widget tree.
    ButtonState leftButton{ButtonState::UP};
    float x{0.0f};
    float y{0.0f};
  };

  Root &root;
  MouseInfo mouse{};

  State state{State::NORMAL};
  Cursor cursor{Cursor::DEFAULT};

  constexpr const StateColors &colors() const {
    return root.theme.stateColors(state);
  }
};
} // namespace katze

#endif // !KATZE_CTX_DCTX_HPP
