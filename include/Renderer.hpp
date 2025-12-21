#ifndef KATZE_RENDERER_HPP
#define KATZE_RENDERER_HPP

#include "core/Rgba.hpp"

struct SDL_Renderer;

namespace katze {
struct Window;

struct Renderer {
  Window &window;
  SDL_Renderer *data{nullptr};
  Rgb backgroundColor{};

  void destroy();

  bool clear();
  bool present();

  bool setDrawColor(Rgb rgb);
  bool setDrawColor(Rgba rgba);
};
} // namespace katze

#endif // !KATZE_RENDERER_HPP
