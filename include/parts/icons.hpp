// A basic implementation of raygui's icons in C++.
// For now, the Katz iconset is hardcoded.
#pragma once
#include <raylib.h>
#include <cstdint>

#ifndef RAYGUI_ICON_SIZE
#define RAYGUI_ICON_SIZE 16 // Size of icons (squared)
#endif

#ifndef RAYGUI_ICON_MAX_ICONS
#define RAYGUI_ICON_MAX_ICONS 256 // Maximum number of icons
#endif

#ifndef RAYGUI_ICON_MAX_NAME_LENGTH
#define RAYGUI_ICON_MAX_NAME_LENGTH 32 // Maximum length of icon name id
#endif

// Icons data is defined by bit array (every bit represents one pixel)
// Those arrays are stored as unsigned int data arrays, so every array
// element defines 32 pixels (bits) of information
// Number of elemens depend on RAYGUI_ICON_SIZE (by default 16x16 pixels)
#ifndef RAYGUI_ICON_DATA_ELEMENTS
#define RAYGUI_ICON_DATA_ELEMENTS (RAYGUI_ICON_SIZE * RAYGUI_ICON_SIZE / 32)
#endif

namespace katzen {
void drawIcon(
    uint8_t iconId, float posX, float posY, float pixelSize, Color color);
} // namespace katzen
