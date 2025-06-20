#include <raylib.h>
#include <functional>
#include "../icons/katz_icons.hpp"
#include "../src/Root.hpp"
#include "../src/widgets.hpp"

int main(void) {
  using katzen::theme::FontStyle;

  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE
                 | FLAG_WINDOW_MAXIMIZED);
  InitWindow(960, 720, "katzen Widget Factory");
  SetTargetFPS(60);
  SetWindowFocused();

  // Set up font styles
  Font font = GetFontDefault();
  FontStyle bodyStyle(font, 18.0f, 2.0f);
  FontStyle titleStyle(font, 36.0f, 2.0f);
  katzen::theme::setFontStyle(bodyStyle);

  // Root and widget creation
  katzen::Root<katzen::Box> root(
      8, katzen::Axis::Y, katzen::Align::CENTER, katzen::Align::CENTER);

  /**
   * Widgets can be emplaced or pushed into container widgets.
   * It's recommended to emplace them to avoid multiple allocations.
   */
  root.child.emplaceBack<katzen::IconLabel>(katzen::KatzIcon::CAT_HEAD,
                                            "katzen Widget Factory",
                                            titleStyle,
                                            [](katzen::IconLabel &self) {
                                              /**
                                               * An example of a setup function.
                                               * The widget calls it on itself
                                               * after the rest of it is
                                               * initialized.
                                               *
                                               * It's a way to set properties
                                               * that are not specified in the
                                               * constructor.
                                               */
                                              self.icon.scale(2);
                                            });

  root.child.emplaceBack<katzen::Label>(
      "Introducing katzen, a dynamic retained mode GUI library written with raylib and C++17!");

  {
    /**
     * Emplacing and pushing to container widgets gives them ownership.
     *
     * However, you can still access the contained widgets with the returned
     * raw pointer.
     *
     * Note that these raw pointers will go out of scope before the main loop,
     * but have been copied by the lambda callbacks.
     */
    katzen::Box *buttons = root.child.emplaceBackGet<katzen::Box>(
        4, katzen::Axis::X, katzen::Align::CENTER, katzen::Align::CENTER);

    katzen::Checkbox *toggler = buttons->emplaceBackGet<katzen::Checkbox>();

    katzen::Button<katzen::Label> *stockButton =
        buttons->emplaceBackGet<katzen::Button<katzen::Label>>(
            katzen::Label("Disabled"));
    stockButton->disable();

    toggler->callback = [stockButton, &root](bool checked) {
      if (!stockButton) return;

      if (checked) {
        stockButton->enable();
        stockButton->child.text.content = "Click me!";
      } else {
        stockButton->disable();
        stockButton->child.text.content = "Disabled";
      }
      root.repaint();
    };

    stockButton->callback = [stockButton, &root]() {
      if (!stockButton) return;

      stockButton->child.text.content = "I got clicked!";
      root.repaint();
      TraceLog(LOG_INFO, stockButton->child.text.content.data());
    };
  }

  root.child.emplaceBack<katzen::Slider>(0.5f);

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
