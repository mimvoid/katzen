#include "bins/Button.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Clickable::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    d.root.messages.push_back(onClick);
  }
  if (child) {
    child->view(d, childRect);
  }
}

void Button::resize(Gctx g, FRect &rect) {
  if (child) {
    Gctx gCopy = g;
    gCopy.shrink(FEdges(padding));
    child->resize(gCopy, childRect);
  } else {
    childRect.w = 0;
    childRect.h = 0;
  }

  rect.w = g.clampWidth(childRect.w + (padding * 2));
  rect.h = g.clampHeight(childRect.h + (padding * 2));
}

void Button::repositionChildren(FRect rect) {
  if (child) {
    child->reposition({rect.x + padding, rect.y + padding}, childRect);
  }
}

void Button::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    d.root.messages.push_back(onClick);
  }

  SDL_FRect drawRect{rect.x, rect.y, rect.w, rect.h};
  StateColors colors = d.colors();

  d.root.renderer.setDrawColor(colors.base);
  SDL_RenderFillRect(d.root.renderer.data, &drawRect);

  if (d.root.theme.borderWidth != 0) {
    d.root.renderer.setDrawColor(colors.border);
    SDL_RenderRect(d.root.renderer.data, &drawRect);
  }

  if (child) {
    child->view(d, childRect);
  }
}
} // namespace katze
