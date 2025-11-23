#pragma once
#include <raylib.h>
#include <optional>
#include <utility>
#include "core/Align.hpp"
#include "core/Dctx.hpp"
#include "core/Edges.hpp"
#include "core/Gctx.hpp"
#include "parts/Bin.hpp"
#include "theme.hpp"

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
template <class WidgetT>
struct Root : Bin<WidgetT> {
  std::optional<Color> customBgColor{};
  Edges padding{0, 0, 0, 0};
  Align halign{Align::CENTER};
  Align valign{Align::CENTER};

  // Construct the Root object's child widget in-place.
  template <typename... Args>
  Root(Args &&...args) : Bin<WidgetT>(std::forward<Args>(args)...) {
    repaint();
  }

  Root(WidgetT &&child) : Bin<WidgetT>(std::move(child)) { repaint(); }

  // Call this when it is needed to manually repaint or update the state.
  void repaint() {
    this->child.repaint(resetGctx());
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
      this->child.repaint(resetGctx());
      m_repaintedLastFrame = false;
    }
  }

  // A shortcut to draw the child widget.
  void draw() {
    ClearBackground(customBgColor.value_or(theme::theme.backgroundColor));

    Dctx d{theme::theme.borderWidth,
           theme::theme.borderRadius,
           theme::theme.iconSize,
           theme::theme.normal};
    this->child.draw(d);

    SetMouseCursor(d.cursor);
  }

private:
  Gctx m_g{};
  bool m_repaintedLastFrame{false};

  /**
   * Sizes and positions the Gctx according to the window size, alignment,
   * and padding.
   */
  Gctx &resetGctx() {
    m_g.reset(padding);

    m_g.x += offset(m_g.w, this->child.width(), halign);
    m_g.y += offset(m_g.h, this->child.height(), valign);

    return m_g;
  }
};
} // namespace katzen
