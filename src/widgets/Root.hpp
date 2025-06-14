#pragma once
#include <type_traits>
#include <utility>
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
  Root(Args &&...args)
      : child(std::forward<Args>(args)...), m_g(Gctx::init(padding)) {
    repaint();
  }

  Root(const T &child) : child(child), m_g(Gctx::init()) {}

  // Call this when it is needed to manually repaint or update the state.
  void repaint() { child.repaint(resetGctx()); }

  /**
   * Checks if the window has been resized and calls repaint automatically.
   * This should usually be invoked every frame.
   */
  void update() {
    if (IsWindowResized()) {
      repaint();
    }
  }

  // A shortcut to draw the child widget.
  void draw() { child.Widget::draw(); }

private:
  Gctx m_g;

  /**
   * Sizes and positions the Gctx according to the window size, alignment,
   * and padding.
   */
  Gctx &resetGctx() {
    m_g.reset(padding);

    m_g.x += offset(m_g.w, child.width(), halign);
    m_g.y += offset(m_g.h, child.height(), valign);

    return m_g;
  }
};
} // namespace katzen::widgets
