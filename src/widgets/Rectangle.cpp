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
  SDL_FRect drawRect{rect.x, rect.y, rect.w, rect.h};
  StateColors colors = d.colors();

  if (filled) {
    d.root.renderer.setDrawColor(colors.base);
    SDL_RenderFillRect(d.root.renderer.data, &drawRect);
  }

  if (bordered) {
    d.root.renderer.setDrawColor(colors.border);
    SDL_RenderRect(d.root.renderer.data, &drawRect);
  }
}
} // namespace katze
