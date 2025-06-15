#include <functional>
#include "../theming/themer.hpp"
#include "Widget.hpp"

namespace katzen {
/**
 * A widget that calls a function when pressed.
 */
template <class T>
struct Button : Widget {
  T child;
  std::function<void()> callback;
  unsigned int borderWidth;

  Button(T &&child, std::function<void()> callback = std::function<void()>())
      : child(std::move(child)),
        callback(callback),
        borderWidth(theme::getProperty(theme::UIntProp::BORDER_WIDTH)) {
    padding.set(8);
  }

  constexpr State state() const { return m_state; }
  constexpr bool enabled() const { return m_state != State::DISABLED; }

  void enable() {
    if (m_state == State::DISABLED) {
      m_state = State::NORMAL;
      m_colors = theme::getStateColors(State::NORMAL);
    }
  }

  void disable() {
    if (m_state != State::DISABLED) {
      m_state = State::DISABLED;

      // Disabled state doesn't update its colors when drawing,
      // so get the colors beforehand
      m_colors = theme::getStateColors(State::DISABLED);
    }
  }

  void toggle() { m_state == State::DISABLED ? enable() : disable(); }

  void repaint(Gctx g) override {
    externalBounds.x = g.w;
    externalBounds.y = g.h;

    position(g);

    g.pad(padding);
    child.repaint(g);

    updateSize();
  }

  void draw(glm::vec2 p) override {
    updateState();

    const Rectangle box = rlRectangle(rect());
    DrawRectangleRec(box, m_colors.base);
    if (borderWidth != 0) {
      DrawRectangleLinesEx(box, borderWidth, m_colors.border);
    }

    child.draw({p.x - x() + child.x(), p.y - y() + child.y()});
  }

protected:
  float measureSize(Axis axis) const override {
    const float size = child.size(axis) + padding.get(axis) + (2 * borderWidth);
    return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
  }

  void updateState() {
    if (m_state == State::DISABLED) return; // Nothing to do

    const State prevState = m_state;

    if (CheckCollisionPointRec(GetMousePosition(), rlRectangle(rect()))) {
      m_state =
          IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? State::ACTIVE : State::FOCUS;

      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && callback) callback();
    } else {
      m_state = State::NORMAL;
    }

    if (m_state != prevState) {
      // The state changed, update colors
      m_colors = theme::getStateColors(m_state);
    }
  }

private:
  State m_state;
  theme::StateColors m_colors = theme::getStateColors(State::NORMAL);
};
} // namespace katzen
