#pragma once
#include <utility>
#include "Dctx.hpp"
#include "Gctx.hpp"
#include "core/Align.hpp"
#include "core/Edges.hpp"
#include "parts/Bin.hpp"
#include "theme/FontStyle.hpp"
#include "theme/Theme.hpp"

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
  Align halign{Align::CENTER};
  Align valign{Align::CENTER};

  bool clearBg = true;

  // Construct the Root object's child widget in-place.
  template <typename... Args>
  Root(Args &&...args) : Bin<WidgetT>(std::forward<Args>(args)...) {
    repaint();
  }

  Root(WidgetT &&child) : Bin<WidgetT>(std::move(child)) { repaint(); }

  // Call this to manually repaint the children.
  void repaint() {
    this->child.repaint(resetGctx());
    m_repaintedLastFrame = true;
  }

  /**
   * Checks if the window has been resized and calls repaint if needed.
   * For most use cases, this should be invoked every frame.
   *
   * HACK: raylib's window size measurements are a little off the frame after
   * window resizing (which is especially bad when switching to fullscreen).
   * To solve this, repaint twice.
   */
  void update() {
    if (IsWindowResized()) {
      repaint();
    } else if (m_repaintedLastFrame) {
      this->child.repaint(resetGctx());
      m_repaintedLastFrame = false;
    }
  }

  /**
   * Clears the background if clearBg is set to true, sets up widget drawing,
   * and updates the mouse cursor.
   */
  void draw() {
    if (clearBg) {
      ClearBackground(theme.backgroundColor);
    }

    Dctx d{theme, font};
    this->child.draw(d);

    SetMouseCursor(d.cursor);
  }

private:
  Gctx m_g{};
  bool m_repaintedLastFrame{false};

  /**
   * Sets the Gctx according to the window size, alignment, and padding, and
   * updates the default font style.
   */
  Gctx &resetGctx() {
    m_g.font = font;
    m_g.reset(padding);

    m_g.x += offset(m_g.w, this->child.width(), halign);
    m_g.y += offset(m_g.h, this->child.height(), valign);

    return m_g;
  }
};
} // namespace katzen
