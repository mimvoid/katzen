#include "Renderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace katze {
void Renderer::destroy() { SDL_DestroyRenderer(data); }

bool Renderer::clear() {
  SDL_SetRenderDrawColor(
    data, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255
  );
  return SDL_RenderClear(data);
}

bool Renderer::present() { return SDL_RenderPresent(data); }

bool Renderer::setDrawColor(Rgb rgb) {
  return SDL_SetRenderDrawColor(data, rgb.r, rgb.g, rgb.b, 255);
}

bool Renderer::setDrawColor(Rgba rgba) {
  return SDL_SetRenderDrawColor(data, rgba.r, rgba.g, rgba.b, rgba.a);
}
} // namespace katze
