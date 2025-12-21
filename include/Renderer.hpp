#ifndef KATZE_RENDERER_HPP
#define KATZE_RENDERER_HPP

#include "core/Rgba.hpp"

struct SDL_Renderer;
struct TTF_TextEngine;

namespace katze {
struct Window;

struct Renderer {
  Window &window;
  Rgb backgroundColor{};

  Renderer(Window &window);

  void destroy();

  constexpr SDL_Renderer *data() const { return m_data; }
  void setData(SDL_Renderer *data);

  constexpr TTF_TextEngine *textEngine() const { return m_textEngine; }

  bool clear();
  bool present();

  bool setDrawColor(Rgb rgb);
  bool setDrawColor(Rgba rgba);

private:
  SDL_Renderer *m_data{nullptr};
  TTF_TextEngine *m_textEngine{nullptr};
};
} // namespace katze

#endif // !KATZE_RENDERER_HPP
