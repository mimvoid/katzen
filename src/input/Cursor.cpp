#include "input/Cursor.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <array>

namespace katze {
struct SystemCursors {
  ~SystemCursors() {
    for (size_t i = 0; i < data.size(); i++) {
      SDL_DestroyCursor(data[i]);
    }
  }

  std::array<SDL_Cursor *, SDL_SYSTEM_CURSOR_COUNT - 1> data{};
};

static SystemCursors cursors{};

bool hideCursor() { return SDL_HideCursor(); }
bool showCursor() { return SDL_ShowCursor(); }
bool isCursorVisible() { return SDL_CursorVisible(); }

bool setCursor(Cursor type) {
  if (type == Cursor::DEFAULT) {
    return SDL_SetCursor(SDL_GetDefaultCursor());
  }

  const uint8_t index = uint8_t(type) - 1;
  SDL_Cursor *cursor = cursors.data[index];

  if (cursor != nullptr) {
    return SDL_SetCursor(cursor);
  }

  cursor = SDL_CreateSystemCursor((SDL_SystemCursor)type);
  cursors.data[index] = cursor;
  return SDL_SetCursor(cursor);
}
} // namespace katze
