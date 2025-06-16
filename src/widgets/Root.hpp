#pragma once
#include <raylib.h>
#include <type_traits>
#include <utility>
#include "../core/Align.hpp"
#include "../theming/themer.hpp"
#include "Widget.hpp"

namespace katzen {
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
                "A katzen Root must have a child derived from Widget");
  T child;

  bool drawBackground = true;
  Edges padding{0, 0, 0, 0};
  Align halign = Align::CENTER;
  Align valign = Align::CENTER;

  // Construct the Root object's child widget in-place.
  template <typename... Args>
  Root(Args &&...args) : child(std::forward<Args>(args)...), m_g(Gctx::init()) {
    repaint();
  }

  Root(const T &child) : child(child), m_g(Gctx::init()) { repaint(); }

  // Call this when it is needed to manually repaint or update the state.
  void repaint() {
    child.repaint(resetGctx());
    m_repaintedLastFrame = true;
  }

  /**
   * Checks if the window has been resized and calls repaint automatically.
   * This should usually be invoked every frame.
   *
   * HACK: raylib's window size measurements are a little off the frame after
   * window resizing (which is especially bad when switching to fullscreen).
   * To solve this, repaint twice.
   */
  void update() {
    if (IsWindowResized()) {
      repaint();
    } else if (m_repaintedLastFrame) {
      child.repaint(resetGctx());
      m_repaintedLastFrame = false;
    }
  }

  // A shortcut to draw the child widget.
  void draw() {
    if (drawBackground) {
      ClearBackground(m_bgColor);
    }

    const theme::Theme &t = theme::getCurrentTheme();
    Dctx d{t.borderWidth,
           t.borderRadius,
           t.iconSize,
           theme::getStateColors(State::NORMAL)};

    child.draw(d);

    SetMouseCursor(d.cursor);
  }

private:
  Gctx m_g;
  Color m_bgColor = theme::getProperty(theme::ColorProp::BACKGROUND);
  bool m_repaintedLastFrame = false;

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
} // namespace katzen
