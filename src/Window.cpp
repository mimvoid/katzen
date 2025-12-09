#include "Window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace katze {
SDL_WindowFlags toSDLFlags(uint8_t flags) {
  SDL_WindowFlags sdlFlags = 0;

  if (flags & WINDOW_ALWAYS_ON_TOP) sdlFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
  if (flags & WINDOW_BORDERLESS) sdlFlags |= SDL_WINDOW_BORDERLESS;
  if (flags & WINDOW_FULLSCREEN) sdlFlags |= SDL_WINDOW_FULLSCREEN;
  if (flags & WINDOW_HIDDEN) sdlFlags |= SDL_WINDOW_HIDDEN;
  if (flags & WINDOW_MAXIMIZED) sdlFlags |= SDL_WINDOW_MAXIMIZED;
  if (flags & WINDOW_MINIMIZED) sdlFlags |= SDL_WINDOW_MINIMIZED;
  if (flags & WINDOW_MODAL) sdlFlags |= SDL_WINDOW_MODAL;
  if (flags & WINDOW_NOT_FOCUSABLE) sdlFlags |= SDL_WINDOW_NOT_FOCUSABLE;
  if (flags & WINDOW_RESIZABLE) sdlFlags |= SDL_WINDOW_RESIZABLE;
  if (flags & WINDOW_TRANSPARENT) sdlFlags |= SDL_WINDOW_TRANSPARENT;
  if (flags & WINDOW_UTILITY) sdlFlags |= SDL_WINDOW_UTILITY;

  return sdlFlags;
}

Window::Window(const char *title, int width, int height, uint8_t windowFlags) {
  SDL_CreateWindowAndRenderer(
    title, width, height, toSDLFlags(windowFlags), &data, &renderer.data
  );
}

uint32_t Window::id() const { return SDL_GetWindowID(data); }

bool Window::valid() const {
  return data && renderer.data && SDL_GetWindowID(data) != 0;
}

void Window::destroy() {
  SDL_HideWindow(data); // Without hiding, the app will look as if it's lagging
  renderer.destroy();
  SDL_DestroyWindow(data);
}

bool Window::show() { return SDL_ShowWindow(data); }
bool Window::hide() { return SDL_HideWindow(data); }
bool Window::maximize() { return SDL_MaximizeWindow(data); }
bool Window::minimize() { return SDL_MinimizeWindow(data); }
bool Window::restore() { return SDL_RestoreWindow(data); }

std::optional<IVec2> Window::minSize() const {
  IVec2 result{};
  bool success = SDL_GetWindowMinimumSize(data, &result.x, &result.y);
  return (success) ? std::make_optional(result) : std::nullopt;
}

bool Window::setMinSize(IVec2 size) {
  return SDL_SetWindowMinimumSize(data, size.x, size.y);
}

std::optional<IVec2> Window::maxSize() const {
  IVec2 result{};
  const bool success = SDL_GetWindowMaximumSize(data, &result.x, &result.y);
  return (success) ? std::make_optional(result) : std::nullopt;
}

bool Window::setMaxSize(IVec2 size) {
  return SDL_SetWindowMaximumSize(data, size.x, size.y);
}

bool Window::setResizable(bool resizable) {
  return SDL_SetWindowResizable(data, resizable);
}
bool Window::setFullScreen(bool fullscreen) {
  return SDL_SetWindowFullscreen(data, fullscreen);
}

std::optional<IVec2> Window::size() const {
  IVec2 result{};
  const bool success = SDL_GetWindowSize(data, &result.x, &result.y);
  return (success) ? std::make_optional(result) : std::nullopt;
}

std::optional<IVec2> Window::sizeInPixels() const {
  IVec2 result{};
  const bool success = SDL_GetWindowSizeInPixels(data, &result.x, &result.y);
  return (success) ? std::make_optional(result) : std::nullopt;
}

bool Window::setSize(IVec2 size) {
  return SDL_SetWindowSize(data, size.x, size.y);
}

const char *Window::title() const { return SDL_GetWindowTitle(data); }

bool Window::setTitle(const char *newTitle) {
  return SDL_SetWindowTitle(data, newTitle);
}
} // namespace katze
