#ifndef KATZE_ROOT_HPP
#define KATZE_ROOT_HPP

#include <memory>
#include <vector>
#include "Reactive.hpp"
#include "Renderer.hpp"
#include "Theme.hpp"
#include "core/Align.hpp"
#include "widgets/Widget.hpp"

namespace katze {
/**
 * Entry-point to a katze widget tree.
 */
struct Root {
  Renderer &renderer;

  Theme theme{};
  AlignVec2 align{Align::CENTER};
  Font font{};

  std::shared_ptr<Widget> child{};
  FRect childRect{};

  // Currently focused reactive widget, such as being hovered over or pressed.
  Reactive *focused{};

  // Callback messages added by reactive widgets.
  std::vector<uint32_t> messages{};

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
