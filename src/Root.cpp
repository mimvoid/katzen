#include "Root.hpp"
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Root::layout() {
  int width, height = 0;
  if (SDL_GetWindowSize(SDL_GetRenderWindow(renderer.data), &width, &height)) {
    layout(width, height);
  }
}

void Root::layout(float width, float height) {
  if (!child) return;

  const Gctx g{width, height};
  child->resize(g, childRect);

  // Once the child's resized, we can know how to align it.
  const float offsetX = offset(g.w, childRect.w, align.x);
  const float offsetY = offset(g.h, childRect.h, align.y);

  child->reposition(Vec2{offsetX, offsetY}, childRect);
}

void Root::view() {
  if (!child) return;

  Dctx d{*this};
  child->view(d, childRect);
}
} // namespace katze
