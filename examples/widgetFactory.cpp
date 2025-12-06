#include <raylib.h>
#include "icons/katz_icons.hpp"
#include "root/Root.hpp"
#include "widgets.hpp"

int main(void) {
  namespace k = katzen;

  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE
                 | FLAG_WINDOW_MAXIMIZED);
  InitWindow(960, 720, "katzen Widget Factory");
  SetTargetFPS(60);
  SetWindowFocused();

  // Set up font styles
  Font font = GetFontDefault();
  k::FontStyle bodyStyle(font, 18.0f, 2.0f);
  k::FontStyle titleStyle(font, 36.0f, 2.0f);

  // Root and widget creation
  k::Root<k::Box> root(8, k::Axis::Y, k::Align::CENTER, k::Align::CENTER);
  root.font = bodyStyle;
  root.child.reserve(4);

  /**
   * Widgets can be emplaced or pushed into container widgets.
   * Emplacing makes fewer allocations, while pushing can be more flexible.
   */

  // Title
  root.child.push(
      k::Box::Builder()
          .spacing(4)
          .emplace<k::Icon>(k::KatzIcon::CAT_HEAD, 2)
          .emplace<k::LabelEx>("katzen Widget Factory", titleStyle, true)
          .build());

  root.child.emplace<k::Label>(
      "Introducing katzen, a dynamic retained mode GUI library written with raylib and C++17!");

  {
    /**
     * You can access contained widgets through katzen's WidgetPtr, a wrapper
     * around weak_ptr<Widget> that can lock and dynamically cast the
     * shared_ptr.
     */
    k::WidgetPtr<k::Box> buttons = root.child.emplaceGet<k::Box>(
        4, k::Axis::X, k::Align::CENTER, k::Align::CENTER);

    std::shared_ptr<k::Box> buttonsBox = buttons.lock();
    if (!buttonsBox) {
      TraceLog(LOG_ERROR, "Failed to create a box for buttons!");
      return 1;
    }
    buttonsBox->reserve(2);

    k::WidgetPtr<k::Button<k::Label>> stockButton =
        buttonsBox->pushGet(k::Button<k::Label>::Builder()
                                .enabled(false)
                                .emplaceChild("Disabled")
                                .onPress([&root](k::Button<k::Label> &self) {
                                  self.child.text = "I got clicked!";
                                  root.repaint();
                                  TraceLog(LOG_INFO, self.child.text);
                                })
                                .build());

    // Toggler
    buttonsBox->emplaceAt<k::Checkbox>(
        0, false, [stockButton, &root](k::Checkbox &self) {
          auto buttonPtr = stockButton.lock();
          if (!buttonPtr) return;

          if (self.checked) {
            buttonPtr->enabled = true;
            buttonPtr->child.text = "Click me!";
          } else {
            buttonPtr->enabled = false;
            buttonPtr->child.text = "Disabled";
          }
          root.repaint();
        });
  }

  root.child.emplace<k::Slider>(0.5f);

  root.repaint();

  while (!WindowShouldClose()) {
    root.update();

    BeginDrawing();
    root.draw();
    EndDrawing();
  }

  UnloadFont(font);
  CloseWindow();
}
