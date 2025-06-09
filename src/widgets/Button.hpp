#include "Widget.hpp"
#include <functional>
#include <raygui.h>

namespace katzen::widgets {
enum class ButtonState { NORMAL, DISABLED, FOCUSED, PRESSED };

struct ButtonColors {
  Color border = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
  Color base = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));
  Color text = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
};

/**
 * A widget that calls a function when pressed.
 */
struct Button : Widget {
  std::unique_ptr<Widget> child;
  std::function<void(void)> callback;
  unsigned int borderWidth;

  template <typename T>
  Button(T &&child)
      : child(std::make_unique<T>(std::move(child))),
        borderWidth(GuiGetStyle(BUTTON, BORDER_WIDTH)) {
    padding.set(8);
  }

  template <typename T>
  Button(T &&child, std::function<void(void)> callback)
      : child(std::make_unique<T>(std::move(child))), callback(callback),
        borderWidth(GuiGetStyle(BUTTON, BORDER_WIDTH)) {
    padding.set(8);
  }

  constexpr ButtonState state() const { return _state; }

  constexpr void enable() {
    if (_state == ButtonState::DISABLED) {
      _state = ButtonState::NORMAL;
    }
  }

  constexpr void disable() {
    if (_state == ButtonState::DISABLED)
      return; // nothing to do

    _state = ButtonState::DISABLED;

    // Disabled state doesn't update its colors when drawing,
    // so get the colors beforehand
    color(ButtonState::DISABLED);
  }

  constexpr void toggle() {
    _state == ButtonState::DISABLED ? enable() : disable();
  }

  void color(ButtonState state);

  void repaint(Gctx g) override;
  void draw(glm::vec2 p) override;

protected:
  float measureSize(Axis axis) const override;
  void updateState();

private:
  ButtonState _state;
  ButtonColors colors;
};
} // namespace katzen::widgets
