#include "parts/icons.hpp"
#include "icons/katz_fill.h"

namespace katzen {
const static unsigned int *guiIconsPtr = katzFillIcons;

void drawIcon(
  uint8_t iconId, float posX, float posY, float pixelSize, Color color
) {
  const int startIndex = iconId * RAYGUI_ICON_DATA_ELEMENTS;
  const int endIndex = startIndex + (RAYGUI_ICON_SIZE * RAYGUI_ICON_SIZE / 32);

  Rectangle rec{posX, posY, pixelSize, pixelSize};

  for (int i = startIndex; i < endIndex; i++) {
    const unsigned int iconBits = guiIconsPtr[i];
    int x = 0;

    for (int k = 0; k < 32; k++) {
      if (iconBits & (1u << k)) {
        rec.x = posX + (x * pixelSize);
        DrawRectangleRec(rec, color);
      }

      if ((k == 15) || (k == 31)) {
        rec.y += pixelSize; // Progress y position
      }

      if (x == RAYGUI_ICON_SIZE - 1)
        x = 0; // Reset
      else
        x++; // Progress x position
    }
  }
}
} // namespace katzen
