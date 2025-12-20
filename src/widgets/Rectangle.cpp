#include "widgets/Rectangle.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Rectangle::resize(Gctx g, FRect &rect) {
  rect.w = g.clampWidth(maxSize.x);
  rect.h = g.clampHeight(maxSize.y);
}

void Rectangle::view(Dctx &d, FRect rect) {
  d.root.renderer.setDrawColor(d.colors().border);

  SDL_FRect drawRect{rect.x, rect.y, rect.w, rect.h};
  if (filled)
    SDL_RenderFillRect(d.root.renderer.data, &drawRect);
  else
    SDL_RenderRect(d.root.renderer.data, &drawRect);
}
} // namespace katze
