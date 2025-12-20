#ifndef KATZE_INPUT_CURSOR_HPP
#define KATZE_INPUT_CURSOR_HPP

#include <cstdint>

namespace katze {
/**
 * katze port of SDL_SystemCursor.
 */
enum class Cursor : uint8_t {
  DEFAULT,
  TEXT,        // Text selection, usually an I-beam.
  WAIT,        // Wait, usually an hourglass, watch, or spinning ball.
  CROSSHAIR,   // Crosshair.
  PROGRESS,    // Program is busy but interactive, usually WAIT with an arrow.
  NWSE_RESIZE, // Double arrow pointing northwest and southeast.
  NESW_RESIZE, // Double arrow pointing northeast and southwest.
  EW_RESIZE,   // Double arrow pointing west and east.
  NS_RESIZE,   // Double arrow pointing north and south.
  MOVE,        // Four arrows pointing north, south, east, and west.
  NOT_ALLOWED, // Not permitted, usually a slashed circle or crossbones.
  POINTER,     // Indicates a link or interactable, usually a pointing hand.
  NW_RESIZE,   // Window resize top-left.
  N_RESIZE,    // Window resize top.
  NE_RESIZE,   // Window resize top-right.
  E_RESIZE,    // Window resize right.
  SE_RESIZE,   // Window resize bottom-right.
  S_RESIZE,    // Window resize bottom.
  SW_RESIZE,   // Window resize bottom-left.
  W_RESIZE,    // Window resize left.
};

// Make the cursor invisible, but still trackable.
bool hideCursor();

// Make the cursor visible.
bool showCursor();

// Return whether the cursor is visible or not.
bool isCursorVisible();

/**
 * Set a system cursor.
 *
 * katze manages these system cursors interally, and automatically frees them
 * when the program exits.
 */
bool setCursor(Cursor type);
} // namespace katze

#endif // !KATZE_INPUT_CURSOR_HPP
