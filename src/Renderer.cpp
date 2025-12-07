#include "Renderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include "Window.hpp"

SDL_Renderer *rendererFromId(uint32_t id) {
  return SDL_GetRenderer(SDL_GetWindowFromID(id));
}

namespace katze {
bool Renderer::clear() {
  SDL_Renderer *rend = rendererFromId(m_window.id());
  SDL_SetRenderDrawColor(
    rend, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255
  );
  return SDL_RenderClear(rend);
}

bool Renderer::present() {
  return SDL_RenderPresent(rendererFromId(m_window.id()));
}
} // namespace katze
