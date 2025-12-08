#include "Root.hpp"
#include <SDL3/SDL_render.h>
#include "bins/Bin.hpp"
#include "ctx/Dctx.hpp"

namespace katze {
void Root::refresh() {
  if (!child) return;

  SDL_Surface *surface =
    SDL_GetWindowSurface(SDL_GetRenderWindow(renderer.data));

  if (!surface) return;

  Gctx g{static_cast<float>(surface->w), static_cast<float>(surface->h)};
  child->resize(g, childData);

  // Once the child's resized, we can know how to align it.
  const float offsetX = offset(g.w, childData.rect.w, align.x);
  const float offsetY = offset(g.h, childData.rect.h, align.y);

  dynReposition(child, Vec2{offsetX, offsetY}, childData);
}

void Root::view() {
  if (!child) return;

  Dctx d{*this};
  child->view(d, childData);
}
} // namespace katze
