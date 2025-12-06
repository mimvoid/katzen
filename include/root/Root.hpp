#pragma once
#include <utility>
#include "../core/Align.hpp"
#include "../core/Edges.hpp"
#include "../parts/Bin.hpp"
#include "../theme/FontStyle.hpp"
#include "../theme/Theme.hpp"
#include "Dctx.hpp"
#include "Gctx.hpp"

namespace katzen {
/**
 * An entry-point for a widget tree.
 *
 * Its job is to detect manage global states like the theme and font style,
 * window resizes, Gctx initialization, and repainting the child widgets.
 *
 * Since Root only holds one widget, it is recommended to use a container widget
 * like Box to hold multiple widgets and handle the layout.
 */
template <class WidgetT>
struct Root : Bin<WidgetT> {
  Theme theme{};
  FontStyle font{};

  Edges padding{0, 0, 0, 0};
  AlignVec2 align{Align::CENTER, Align::CENTER};

  bool clearBg = true;

  Root() = default;
  Root(WidgetT &&child) : Bin<WidgetT>(std::move(child)) {}

  // Construct the Root object's child widget in-place.
  template <typename... Args>
  Root(Args &&...args) : Bin<WidgetT>(std::forward<Args>(args)...) {}

  // Call this to manually repaint the children.
  void repaint() {
    Gctx g{font, padding};
    this->child.resize(g);

    // When repainting, we didn't consider the Root's alignment, because the
    // sizes would be based on an outdated screen size. Therefore, we translate
    // the children after we have measured their sizes.
    const float offsetX = offset(g.w, this->child.width(), align.x);
    const float offsetY = offset(g.h, this->child.height(), align.y);

    this->child.reposition(Vec2{padding.left + offsetX, padding.top + offsetY});
  }

  /**
   * Checks if the window has been resized and calls repaint if needed.
   * For most use cases, this should be invoked every frame.
   */
  void update() {
    if (IsWindowResized()) repaint();
  }

  /**
   * Clears the background if clearBg is set to true, sets up widget drawing,
   * and updates the mouse cursor.
   */
  void draw() {
    if (clearBg) {
      ClearBackground((Color)theme.backgroundColor);
    }

    Dctx d{theme, font};
    this->child.draw(d);

    SetMouseCursor(d.cursor);
  }
};

template <class WidgetT>
Root(WidgetT &&) -> Root<WidgetT>;
} // namespace katzen
