#include "Root.hpp"
#include <SDL3/SDL_render.h>
#include "Window.hpp"
#include "ctx/Dctx.hpp"

namespace katze {
void Root::layout() {
  std::optional<IVec2> size = renderer.window.size();
  if (size.has_value()) {
    layout(size->x, size->y);
  }
}

void Root::layout(float width, float height) {
  if (!child) return;

  const Gctx g{font, width, height};
  child->resize(g, childRect);

  // Once the child's resized, we can know how to align it.
  const float offsetX = offset(g.w, childRect.w, align.x);
  const float offsetY = offset(g.h, childRect.h, align.y);

  child->reposition(Vec2{offsetX, offsetY}, childRect);
}

void Root::view() {
  if (!child) return;

  Dctx d{*this};

  // Set the mouse info for this window, if any.
  if (renderer.window.focused()) {
    const MouseState mouse = mouseState();
    d.mouse = Dctx::MouseInfo{true, mouse.leftButton, mouse.x, mouse.y};
  }

  child->view(d, childRect);
  setCursor(d.cursor);
}
} // namespace katze
