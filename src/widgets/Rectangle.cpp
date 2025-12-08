#include "widgets/Rectangle.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Rectangle::view(Dctx &d, const WidgetData &wData) {
  Rgb border = d.colors().border;
  SDL_SetRenderDrawColor(
    d.root.renderer.data, border.r, border.g, border.b, 255
  );

  SDL_FRect drawRect{wData.rect.x, wData.rect.y, wData.rect.w, wData.rect.h};
  SDL_RenderRect(d.root.renderer.data, &drawRect);
}
} // namespace katze
