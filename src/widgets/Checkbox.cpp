#include "widgets/Checkbox.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Checkbox::resize(Gctx g, FRect &rect) {
  const float checkSize = g.font.size();
  rect.w = g.clampWidth(checkSize);
  rect.h = g.clampHeight(checkSize);
}

void Checkbox::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    checked = !checked;
    d.root.messages.push_back(onCheck);
  }

  const StateColors &colors = d.colors();
  const SDL_FRect rec{rect.x, rect.y, rect.w, rect.h};

  d.root.renderer.setDrawColor(colors.base);
  SDL_RenderFillRect(d.root.renderer.data(), &rec);

  const bool drawBorder = d.root.theme.borderWidth != 0;
  if (drawBorder || checked) {
    d.root.renderer.setDrawColor(colors.border);

    if (drawBorder) {
      SDL_RenderRect(d.root.renderer.data(), &rec);
    }
    if (checked) {
      const float gap = d.root.theme.borderWidth * 2;
      const SDL_FRect checkRect{
        rect.x + gap, rect.y + gap, rect.w - (2 * gap), rect.h - (2 * gap)
      };
      SDL_RenderFillRect(d.root.renderer.data(), &checkRect);
    }
  }
}
} // namespace katze
