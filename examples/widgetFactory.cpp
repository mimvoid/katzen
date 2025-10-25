#include <raylib.h>
#include "../include/Root.hpp"
#include "../include/icons/katz_icons.hpp"
#include "../include/widgets.hpp"

int main(void) {
  namespace k = katzen;
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
  k::theme::setFontStyle(bodyStyle);

  // Root and widget creation
  k::Root<k::Box> root(8, k::Axis::Y, k::Align::CENTER, k::Align::CENTER);

  {
    /**
     * Widgets can be emplaced or pushed into container widgets.
     * It's recommended to emplace them to avoid multiple allocations.
     */
    k::Box title(4);
    title.emplace<k::Icon>(k::KatzIcon::CAT_HEAD, 2);
    title.emplace<k::Label>("katzen Widget Factory", true, titleStyle);

    root.child.push(std::move(title));
  }

  root.child.emplace<k::Label>(
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
    k::Box *buttons = root.child.emplaceGet<k::Box>(
        4, k::Axis::X, k::Align::CENTER, k::Align::CENTER);

    k::Checkbox *toggler = buttons->emplaceGet<k::Checkbox>();

    k::Button<k::Label> *stockButton =
        buttons->emplaceGet<k::Button<k::Label>>(k::Label("Disabled"));
    stockButton->disable();

    toggler->onCheck = [stockButton, &root](bool checked) {
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

    stockButton->onPress = [stockButton, &root]() {
      if (!stockButton) return;

      stockButton->child.text.content = "I got clicked!";
      root.repaint();
      TraceLog(LOG_INFO, stockButton->child.text.content);
    };
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
