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

std::optional<IVec2> fromSizeResult(int *x, int *y, bool success) {
  if (success && x != nullptr && y != nullptr) {
    return std::make_optional<IVec2>(*x, *y);
  }
  return std::nullopt;
}

Window::Window(const char *title, int width, int height, uint8_t windowFlags) {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (SDL_CreateWindowAndRenderer(
        title, width, height, toSDLFlags(windowFlags), &window, &renderer
      )) {
    m_id = SDL_GetWindowID(window);
  }
}

bool Window::valid() const { return SDL_GetWindowFromID(m_id) != nullptr; }

void Window::destroy() {
  SDL_Window *window = SDL_GetWindowFromID(m_id);

  // Keeping the window visible will look as if the app is lagging.
  SDL_HideWindow(window);

  SDL_DestroyRenderer(SDL_GetRenderer(window));
  SDL_DestroyWindow(window);
}

bool Window::show() { return SDL_ShowWindow(SDL_GetWindowFromID(m_id)); }
bool Window::hide() { return SDL_HideWindow(SDL_GetWindowFromID(m_id)); }
bool Window::maximize() {
  return SDL_MaximizeWindow(SDL_GetWindowFromID(m_id));
}
bool Window::minimize() {
  return SDL_MinimizeWindow(SDL_GetWindowFromID(m_id));
}
bool Window::restore() { return SDL_RestoreWindow(SDL_GetWindowFromID(m_id)); }

std::optional<IVec2> Window::minSize() const {
  int *w = nullptr;
  int *h = nullptr;
  bool success = SDL_GetWindowMinimumSize(SDL_GetWindowFromID(m_id), w, h);
  return fromSizeResult(w, h, success);
}

bool Window::setMinSize(IVec2 size) {
  return SDL_SetWindowMinimumSize(SDL_GetWindowFromID(m_id), size.x, size.y);
}

std::optional<IVec2> Window::maxSize() const {
  int *w = nullptr;
  int *h = nullptr;
  bool success = SDL_GetWindowMaximumSize(SDL_GetWindowFromID(m_id), w, h);
  return fromSizeResult(w, h, success);
}

bool Window::setMaxSize(IVec2 size) {
  return SDL_SetWindowMaximumSize(SDL_GetWindowFromID(m_id), size.x, size.y);
}

bool Window::setResizable(bool resizable) {
  return SDL_SetWindowResizable(SDL_GetWindowFromID(m_id), resizable);
}
bool Window::setFullScreen(bool fullscreen) {
  return SDL_SetWindowFullscreen(SDL_GetWindowFromID(m_id), fullscreen);
}

std::optional<IVec2> Window::size() const {
  int *w = nullptr;
  int *h = nullptr;
  bool success = SDL_GetWindowSize(SDL_GetWindowFromID(m_id), w, h);
  return fromSizeResult(w, h, success);
}

std::optional<IVec2> Window::sizeInPixels() const {
  int *w = nullptr;
  int *h = nullptr;
  bool success = SDL_GetWindowSizeInPixels(SDL_GetWindowFromID(m_id), w, h);
  return fromSizeResult(w, h, success);
}

bool Window::setSize(IVec2 size) {
  return SDL_SetWindowSize(SDL_GetWindowFromID(m_id), size.x, size.y);
}

const char *Window::title() const {
  return SDL_GetWindowTitle(SDL_GetWindowFromID(m_id));
}

bool Window::setTitle(const char *newTitle) {
  return SDL_SetWindowTitle(SDL_GetWindowFromID(m_id), newTitle);
}
} // namespace katze
