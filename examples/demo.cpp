#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>
#include "Root.hpp"
#include "Window.hpp"
#include "app.hpp"
#include "bins.hpp"
#include "icons/katz.hpp"
#include "widgets.hpp"

#include "tamzen/tamzen.hpp"

enum Messages : uint8_t { CHECK, BUTTON_CLICK, SLIDER_MOVE };

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
  Font tamzen = loadTamzen7x14Font();
  Font title = tamzen.copy();
  title.setSize(28.0f);

  Root root{win.renderer};
  root.font = tamzen;

  // Widgets that will be referenced later.
  std::shared_ptr checkbox = std::make_shared<Checkbox>(false, CHECK);
  std::shared_ptr buttonText = std::make_shared<Label>("Disabled");
  std::shared_ptr button = std::make_shared<Button>(buttonText, BUTTON_CLICK);
  button->enabled = false;

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
      Box{4, Axis::X, {Align::CENTER}, {checkbox, button}},
      Slider{0.5f, SLIDER_MOVE},
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

    for (uint32_t msg : root.messages) {
      switch (msg) {
      case CHECK:
        if (checkbox->checked) {
          button->enabled = true;
          buttonText->text = "Click me!";
        } else {
          button->enabled = false;
          buttonText->text = "Disabled";
        }
        root.layout();
        break;
      case BUTTON_CLICK:
        buttonText->text = "I got clicked!";
        root.layout();
        SDL_Log("INFO: %s", buttonText->text);
        break;
      default: break;
      }
    }
    root.messages.clear();

    SDL_Delay(1000 / 60);
  }

  tamzen.close();
  title.close();

  win.destroy();
  katze::quit();

  return 0;
}
