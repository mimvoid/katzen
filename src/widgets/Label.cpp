#include "widgets/Label.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Label::resize(Gctx g, FRect &rect) { resizeForFont(g.font, g, rect); }
void Label::view(Dctx &d, FRect rect) { viewForFont(d.root.font, d, rect); }

void Label::resizeForFont(Font font, const Gctx &g, FRect &rect) {
  if (empty()) {
    rect.w = 0;
    rect.h = 0;
    return;
  }

  int width = 0;
  int height = 0;

  // If wrapWords is false, set wrap_width to 0 to still wrap on \n
  TTF_GetStringSizeWrapped(
    font.data, text, 0, wrapWords ? g.w : 0, &width, &height
  );

  rect.w = g.clampWidth(width);
  rect.h = g.clampHeight(height);
}

void Label::viewForFont(Font font, Dctx &d, FRect rect) {
  if (empty()) {
    return; // Nothing to draw
  }

  Rgb color = d.colors().text;
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(
    font.data,
    text,
    0,
    SDL_Color{color.r, color.g, color.b, 255},
    wrapWords ? rect.w : 0
  );

  if (surface) {
    SDL_Texture *texture =
      SDL_CreateTextureFromSurface(d.root.renderer.data, surface);

    if (texture) {
      SDL_FRect dst{rect.x, rect.y, rect.w, rect.h};
      SDL_RenderTexture(d.root.renderer.data, texture, nullptr, &dst);
    }

    SDL_DestroyTexture(texture);
  }

  SDL_DestroySurface(surface);
}
} // namespace katze
