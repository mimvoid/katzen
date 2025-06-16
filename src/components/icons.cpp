#include "icons.hpp"
#include "../../icons/katz_fill.h"

namespace katzen {
const static unsigned int *guiIconsPtr = katzFillIcons;

void drawIcon(
    uint8_t iconId, float posX, float posY, uint8_t pixelSize, Color color) {
#define BIT_CHECK(a, b) ((a) & (1u << (b)))

  for (int i = 0, y = 0; i < RAYGUI_ICON_SIZE * RAYGUI_ICON_SIZE / 32; i++) {
    for (int k = 0; k < 32; k++) {
      if (BIT_CHECK(guiIconsPtr[iconId * RAYGUI_ICON_DATA_ELEMENTS + i], k)) {
        const Rectangle rec{posX + (k % RAYGUI_ICON_SIZE) * pixelSize,
                            posY + y * pixelSize,
                            (float)pixelSize,
                            (float)pixelSize};
        DrawRectangleRec(rec, color);
      }

      if ((k == 15) || (k == 31)) y++;
    }
  }
}
} // namespace katzen
