#ifndef KATZE_ROOT_HPP
#define KATZE_ROOT_HPP

#include <memory>
#include "Renderer.hpp"
#include "core/Align.hpp"
#include "theme/Theme.hpp"
#include "widgets/Widget.hpp"

namespace katze {
/**
 * Entry-point to a katze widget tree.
 */
struct Root {
  Renderer &renderer;

  Theme theme{};
  AlignVec2 align{Align::CENTER, Align::CENTER};
  Font font{};

  std::shared_ptr<Widget> child{};
  FRect childRect{};

  Root(Renderer &renderer, Theme theme = {})
    : renderer(renderer), theme(theme) {}

  /**
   * Find the size of the window and resize and reposition the widgets.
   */
  void layout();

  /**
   * Given a known window size, resize and reposition the widgets in the tree.
   */
  void layout(float width, float height);

  /**
   * Draw the widgets and collect messages.
   */
  void view();
};
} // namespace katze

#endif // !KATZE_ROOT_HPP
