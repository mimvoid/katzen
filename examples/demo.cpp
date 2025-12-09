#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>
#include "Root.hpp"
#include "Window.hpp"
#include "app.hpp"
#include "widgets/Rectangle.hpp"

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
  const uint32_t winId = win.id();

  k::Root root{win.renderer};
  root.childData.padding.set(64);
  root.child = std::make_shared<k::Rectangle>();

  while (!k::shouldQuit()) {
    for (k::ResizeData &resizeData : k::resizedWindows()) {
      if (resizeData.windowId == winId) {
        root.refresh(resizeData.width, resizeData.height);
      }
    }

    win.renderer.clear();
    root.view();
    win.renderer.present();

    SDL_Delay(1000 / 60);
  }

  win.destroy();
  k::quit();

  return 0;
}
