#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>
#include "Root.hpp"
#include "Window.hpp"
#include "app.hpp"
#include "bins/Box.hpp"
#include "bins/Padding.hpp"
#include "icons/katz.hpp"
#include "widgets/Icon.hpp"
#include "widgets/Label.hpp"
#include "widgets/LabelEx.hpp"
#include "widgets/Rectangle.hpp"

#include "tiny/tiny.hpp"

int main(void) {
  using namespace katze;
  katze::init("katze Widget Factory", "0.1.0", "com.katze.widgetFactory");

  Window win{
    "katze Widget Factory", 960, 720, WINDOW_RESIZABLE | WINDOW_MAXIMIZED
  };
  if (!win.valid()) {
    SDL_Log("Failed to initialize window: %s", SDL_GetError());
    katze::quit();
    return 1;
  }
  win.renderer.backgroundColor = {255, 245, 225};

  const uint32_t winId = win.id();
  IconBits catHead{iconBitsById(KatzIcon::CAT_HEAD, katzFill)};

  // Load fonts
  Font tiny = loadTinyFont();
  Font title = tiny.copy();
  title.setSize(28.0f);

  Root root{win.renderer};
  root.font = tiny;

  root.child = std::make_shared<Padding>(
    4.0f,
    Box{
      4,
      Axis::Y,
      {Align::CENTER},
      Box{
        4,
        Axis::X,
        {Align::CENTER},
        Icon{catHead, 2},
        LabelEx{title, "katze Widget Factory"},
      },
      Label{
        "Introducing katze, a dynamic retained mode GUI library written with SDL and C++17!"
      },
      Rectangle{128.0f, 128.0f},
    }
  );

  while (!katze::shouldQuit()) {
    for (ResizeData &resizeData : katze::resizedWindows()) {
      if (resizeData.windowId == winId) {
        root.layout(resizeData.width, resizeData.height);
      }
    }

    win.renderer.clear();
    root.view();
    win.renderer.present();

    SDL_Delay(1000 / 60);
  }

  tiny.close();
  title.close();

  win.destroy();
  katze::quit();

  return 0;
}
