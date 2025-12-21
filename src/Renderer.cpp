#include "Renderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.hpp"

namespace katze {
Renderer::Renderer(Window &window)
  : window(window),
    m_data(SDL_GetRenderer(window.data)),
    m_textEngine(TTF_CreateRendererTextEngine(m_data)) {}

void Renderer::destroy() {
  TTF_DestroyRendererTextEngine(m_textEngine);
  SDL_DestroyRenderer(m_data);
}

void Renderer::setData(SDL_Renderer *renderer) {
  m_data = renderer;
  m_textEngine = TTF_CreateRendererTextEngine(renderer);
}

bool Renderer::clear() {
  SDL_SetRenderDrawColor(
    m_data, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255
  );
  return SDL_RenderClear(m_data);
}

bool Renderer::present() { return SDL_RenderPresent(m_data); }

bool Renderer::setDrawColor(Rgb rgb) {
  return SDL_SetRenderDrawColor(m_data, rgb.r, rgb.g, rgb.b, 255);
}

bool Renderer::setDrawColor(Rgba rgba) {
  return SDL_SetRenderDrawColor(m_data, rgba.r, rgba.g, rgba.b, rgba.a);
}
} // namespace katze
