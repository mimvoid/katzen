#include "widgets/Icon.hpp"
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Icon::resize(Gctx g, FRect &rect) {
  const float iconSize = m_scale * KATZE_ICON_SIZE;
  rect.w = g.clampWidth(iconSize);
  rect.h = g.clampHeight(iconSize);
}

void Icon::view(Dctx &d, FRect rect) {
  const Rgb color = d.colors().text;
  SDL_SetRenderDrawColor(d.root.renderer.data, color.r, color.g, color.b, 255);

  drawIcon(
    d.root.renderer.data, bits, rect.x, rect.y, m_scale * d.root.theme.iconSize
  );
}
} // namespace katze
