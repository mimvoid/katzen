#ifndef KATZE_CTX_DCTX_HPP
#define KATZE_CTX_DCTX_HPP

#include "../Root.hpp"
#include "../core/State.hpp"

struct SDL_Renderer;

namespace katze {
enum class Cursor : uint8_t { DEFAULT, POINTER };

/**
 * A drawing context that provides theme settings and stores a widget state
 * that can be passed to children.
 */
struct Dctx {
  Root &root;

  // FontStyle font{};
  State state{State::NORMAL};
  Cursor cursor{Cursor::DEFAULT};

  constexpr const StateColors &colors() const {
    return root.theme.stateColors(state);
  }
};
} // namespace katze

#endif // !KATZE_CTX_DCTX_HPP
