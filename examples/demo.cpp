#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>
#include "Window.hpp"
#include "app.hpp"

namespace k = katze;

int main(void) {
  k::init("katze Widget Factory", "0.1.0", "com.katze.widgetFactory");

  k::Window win{
    "katze Widget Factory", 960, 720, k::WINDOW_RESIZABLE | k::WINDOW_MAXIMIZED
  };
  if (!win.valid()) {
    SDL_Log("Failed to initialize window: %s", SDL_GetError());
    k::quit();
    return 1;
  }

  while (!k::shouldQuit()) {
    win.renderer.clear();
    win.renderer.present();

    SDL_Delay(1000 / 60);
  }

  win.destroy();
  k::quit();

  return 0;
}
