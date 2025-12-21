#include "input/mouse.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <vector>

namespace katze {
bool hasMouse() { return SDL_HasMouse(); }

MouseState mouseState() {
  MouseState state{};

  ButtonState transitionState{ButtonState::RELEASED};
  uint32_t eventType{SDL_EVENT_MOUSE_BUTTON_UP};

  if (SDL_GetMouseState(&state.x, &state.y) & SDL_BUTTON_LMASK) {
    // The left mouse button is actually down, change state and event types.
    state.leftButton = ButtonState::DOWN;
    transitionState = ButtonState::PRESSED;
    eventType = SDL_EVENT_MOUSE_BUTTON_DOWN;
  }

  // Allocate events for five buttons per mouse, which is likely enough.
  int mouseCount = 0;
  SDL_free(SDL_GetMice(&mouseCount));
  std::vector<SDL_Event> events{static_cast<size_t>(mouseCount) * 5};

  // Query for button press or release events.
  const int eventCount = SDL_PeepEvents(
    events.data(), events.size(), SDL_GETEVENT, eventType, eventType
  );

  if (eventCount > 0) {
    // Store events we didn't process.
    std::vector<SDL_Event> addEvents{};
    addEvents.reserve(eventCount);

    for (int i = 0; i < eventCount; i++) {
      SDL_Event &event = events[i];

      if (event.button.button == SDL_BUTTON_LEFT) {
        state.leftButton = transitionState;
        state.leftClicks = event.button.clicks;
      } else {
        addEvents.push_back(event);
      }
    }

    // Add back events we didn't process.
    SDL_PeepEvents(
      addEvents.data(), addEvents.size(), SDL_ADDEVENT, eventType, eventType
    );
  }

  return state;
}
} // namespace katze
