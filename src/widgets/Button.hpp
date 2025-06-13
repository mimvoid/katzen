#include <functional>
#include <memory>
#include "../theming/themer.hpp"
#include "Widget.hpp"

namespace katzen::widgets {
/**
 * A widget that calls a function when pressed.
 */
struct Button : Widget {
  std::unique_ptr<Widget> child;
  std::function<void(void)> callback;
  unsigned int borderWidth;

  template <typename T>
  Button(T &&child) : Button(child, std::function<void(void)>()) {}

  template <typename T>
  Button(T &&child, std::function<void(void)> callback)
      : child(std::make_unique<T>(std::move(child))),
        callback(callback),
        borderWidth(theme::getProperty(theme::UIntProp::BORDER_WIDTH)) {
    padding.set(8);
  }

  constexpr State state() const { return m_state; }

  constexpr void enable() {
    if (m_state == State::DISABLED) {
      m_state = State::NORMAL;
    }
  }

  void disable();
  void toggle() { m_state == State::DISABLED ? enable() : disable(); }

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureSize(Axis axis) const override;
  void updateState();

private:
  State m_state;
  theme::StateColors m_colors = theme::getStateColors(State::NORMAL);
};
} // namespace katzen::widgets
