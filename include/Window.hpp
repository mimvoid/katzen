#ifndef KATZE_WINDOW_HPP
#define KATZE_WINDOW_HPP

#include <cstdint>
#include <optional>
#include "core/Vec2.hpp"
#include "Renderer.hpp"

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

struct Window {
  Renderer renderer{*this};

  Window(const char *title, int width, int height, uint8_t windowFlags = 0);

  constexpr uint32_t id() const { return m_id; }

  bool valid() const;
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

private:
  uint32_t m_id{0};
};
} // namespace katze

#endif // !KATZE_WINDOW_HPP
