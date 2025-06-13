#pragma once
#include <type_traits>
#include "../core/Align.hpp"
#include "Widget.hpp"

namespace katzen::widgets {
/**
 * An entry-point for creating a widget tree.
 *
 * Its job is to detect window resizes, handle Gctx initialization, and repaint
 * the child widgets.
 *
 * Since Root only holds one widget, it is recommended to use a container widget
 * like Box to hold multiple widgets and handle the layout.
 */
template <typename T>
struct Root {
  static_assert(std::is_base_of_v<Widget, T>,
                "rootWidget is derived from katzen's Widget");
  T child;

  Edges padding{0, 0, 0, 0};
  Align halign = Align::CENTER;
  Align valign = Align::CENTER;

  // Construct the Root object's child widget in-place.
  template <typename... Args>
  Root(Args &&...args);

  // Call this when it is needed to manually repaint or update the state.
  constexpr void repaint() { child.repaint(resetGctx()); }

  /**
   * Checks if the window has been resized and calls repaint automatically.
   * This should usually be invoked every frame.
   */
  constexpr void update() {
    if (IsWindowResized()) {
      repaint();
    }
  }

  // A shortcut to draw the child widget.
  constexpr void draw() { child.Widget::draw(); }

private:
  katzen::Gctx m_g;

  /**
   * Sizes and positions the Gctx according to the window size, alignment,
   * and padding.
   */
  katzen::Gctx &resetGctx();
};
} // namespace katzen::widgets
