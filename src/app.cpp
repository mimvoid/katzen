#include "app.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <climits>

namespace katze {
bool init(const char *name, const char *version, const char *appId) {
  SDL_SetAppMetadata(name, version, appId);
  return SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
}

bool shouldQuit() {
  SDL_PumpEvents();
  return SDL_HasEvent(SDL_EVENT_QUIT);
}

void quit() { SDL_Quit(); }

} // namespace katze
