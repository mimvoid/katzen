#ifndef KATZE_WINDOW_HPP
#define KATZE_WINDOW_HPP

#include <cstdint>
#include <optional>
#include <vector>
#include "core/Vec2.hpp"
#include "Renderer.hpp"

struct SDL_Window;

namespace katze {
enum WindowFlags : uint16_t {
  WINDOW_MAXIMIZED = 1,
  WINDOW_MINIMIZED = 2,
  WINDOW_FULLSCREEN = 4,
  WINDOW_RESIZABLE = 8,
  WINDOW_HIDDEN = 16,
  WINDOW_MODAL = 32,
  WINDOW_BORDERLESS = 64,
  WINDOW_ALWAYS_ON_TOP = 128,
  WINDOW_UTILITY = 256,
  WINDOW_TRANSPARENT = 512,
  WINDOW_NOT_FOCUSABLE = 1024,
};

struct ResizeData {
  uint32_t windowId{0};
  int width{0};
  int height{0};
};

/**
 * Find windows that have been resized and return their IDs and sizes.
 */
std::vector<ResizeData> resizedWindows();

struct Window {
  Renderer renderer{};
  SDL_Window *data{nullptr};

  Window(const char *title, int width, int height, uint8_t windowFlags = 0);

  uint32_t id() const;

  bool valid() const;

  /**
   * Destroy the window and its renderer.
   */
  void destroy();

  bool show();
  bool hide();
  bool maximize();
  bool minimize();
  bool restore();

  std::optional<IVec2> minSize() const;
  bool setMinSize(IVec2 size);

  std::optional<IVec2> maxSize() const;
  bool setMaxSize(IVec2 size);

  bool setResizable(bool resizable);
  bool setFullScreen(bool fullscreen);

  std::optional<IVec2> size() const;
  std::optional<IVec2> sizeInPixels() const;

  bool setSize(IVec2 size);

  const char *title() const;
  bool setTitle(const char *newTitle);
};
} // namespace katze

#endif // !KATZE_WINDOW_HPP
