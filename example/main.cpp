#include <raylib.h>
#include <functional>
#include "../icons/katz_icons.hpp"
#include "../src/widgets.hpp"

int main(void) {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE
                 | FLAG_WINDOW_MAXIMIZED);
  InitWindow(960, 720, "katzen Widget Factory");
  SetTargetFPS(60);
  SetWindowFocused();

  // Set up katzen fonts
  katzen::theme::loadFont(GetFontDefault());
  katzen::theme::setFontProperties(18, 2.0f);

  const size_t titleId = katzen::theme::loadFont(GetFontDefault());
  katzen::theme::setFontProperties(48, 2.0f, titleId);

  // Root and widget creation
  katzen::Root<katzen::Box> root(
      8, katzen::Axis::Y, katzen::Align::CENTER, katzen::Align::CENTER);

  root.child.emplace<katzen::IconLabel>(
      katzen::KatzIcon::CAT_HEAD,
      "katzen Widget Factory",
      1,
      [](katzen::IconLabel &self) { self.icon.scale(2); });

  root.child.emplace<katzen::Label>(
      "Introducing katzen, a dynamic retained mode GUI library written with raylib and C++17!");

  // Emplacing and pushing to container widgets gives them ownership.
  // However, you can still access the contained widgets with the returned
  // pointer!
  katzen::Box *buttons = root.child.emplaceGet<katzen::Box>(
      4, katzen::Axis::X, katzen::Align::CENTER, katzen::Align::CENTER);

  katzen::Checkbox *toggler = buttons->emplaceGet<katzen::Checkbox>();

  katzen::Button<katzen::Label> *stockButton =
      buttons->emplaceGet<katzen::Button<katzen::Label>>(
          katzen::Label("Disabled"));
  stockButton->disable();

  toggler->callback = [&stockButton, &root](bool checked) {
    if (checked) {
      stockButton->enable();
      stockButton->child.text.content = "Click me!";
    } else {
      stockButton->disable();
      stockButton->child.text.content = "Disabled";
    }
    root.repaint();
  };

  stockButton->callback = [&stockButton, &root]() {
    stockButton->child.text.content = "I got clicked!";
    root.repaint();
    TraceLog(LOG_INFO, stockButton->child.text.content.data());
  };

  root.child.emplace<katzen::Slider>(0.5f);

  root.repaint();

  while (!WindowShouldClose()) {
    root.update();

    BeginDrawing();
    root.draw();
    EndDrawing();
  }

  CloseWindow();
}
