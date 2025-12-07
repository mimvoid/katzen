#ifndef KATZE_RENDERER_HPP
#define KATZE_RENDERER_HPP

#include "core/Rgba.hpp"

namespace katze {
struct Window;

struct Renderer {
  Rgb backgroundColor{};

  Renderer(Window &parentWindow) : m_window(parentWindow) {}

  const Window &window() const { return m_window; }

  bool clear();
  bool present();

private:
  Window &m_window;
};
} // namespace katze

#endif // !KATZE_RENDERER_HPP
