#ifndef KATZE_INPUT_MOUSE_HPP
#define KATZE_INPUT_MOUSE_HPP

#include <cstdint>

namespace katze {
enum class ButtonState : uint8_t {
  UP,       // Button is up (i.e. not being pressed).
  PRESSED,  // Button was up, and is now down.
  DOWN,     // Button continues to be down.
  RELEASED, // Button was down, and is now up.
};

enum class MouseButton : uint8_t {
  LEFT,   // Left mouse button.
  MIDDLE, // Middle mouse button.
  RIGHT,  // Right mouse button.
  X1,     // Side mouse button 1.
  X2,     // Side mouse button 2.
};

struct MouseState {
  uint32_t windowId{0}; // The window with mouse focus, if any.
  float x{0.0f};        // x-position from the focused window's top-left corner.
  float y{0.0f};        // y-position from the focused window's top-left corner.
  uint8_t leftClicks{0};
  ButtonState leftButton{ButtonState::UP};
};

// Return whether a mouse is currently connected.
bool hasMouse();

/**
 * Peeks events and queries SDL's cache for the mouse left button state and
 * cursor position relative to the focused window.
 */
MouseState mouseState();
} // namespace katze

#endif // !KATZE_INPUT_MOUSE_HPP
