#include "Root.hpp"
#include <SDL3/SDL_render.h>
#include "bins/Bin.hpp"
#include "ctx/Dctx.hpp"

namespace katze {
void Root::refresh() {
  int width, height = 0;
  if (SDL_GetWindowSize(SDL_GetRenderWindow(renderer.data), &width, &height)) {
    refresh(width, height);
  }
}

void Root::refresh(int width, int height) {
  Gctx g{static_cast<float>(width), static_cast<float>(height)};
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
