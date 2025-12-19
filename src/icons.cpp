#include "icons.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

namespace katze {
IconBits iconBitsById(uint8_t iconId, const IconSet &iconSet) {
  IconBits bits{};
  const size_t startIdx = static_cast<int>(iconId) * KATZE_ICON_ITEM_COUNT;

  if (startIdx + KATZE_ICON_ITEM_COUNT <= iconSet.size()) {
    for (size_t i = 0; i < KATZE_ICON_ITEM_COUNT; i++) {
      bits[i] = iconSet[startIdx + i];
    }
  }

  return bits;
}

void drawIcon(
  SDL_Renderer *rend,
  const IconBits &bits,
  float posX,
  float posY,
  float pixelSize
) {
  std::vector<SDL_FRect> recs{};
  recs.reserve(KATZE_ICON_BIT_SIZE / 2); // reduce allocations from pushing

  float y = posY;
  uint8_t col = 0;

  for (uint32_t bitItem : bits) {
    for (size_t i = 0; i < KATZE_U32_BIT_SIZE; i++) {
      if (bitItem & (1u << i)) {
        recs.push_back(
          SDL_FRect{posX + (col * pixelSize), y, pixelSize, pixelSize}
        );
      }

      if (col == KATZE_ICON_SIZE - 1) {
        col = 0;        // Reset column
        y += pixelSize; // Progress y
      } else {
        col++; // Progress column
      }
    }
  }

  SDL_RenderFillRects(rend, recs.data(), recs.size());
}

void drawIcon(
  SDL_Renderer *rend,
  uint8_t iconId,
  const IconSet &iconSet,
  float posX,
  float posY,
  float pixelSize
) {
  drawIcon(rend, iconBitsById(iconId, iconSet), posX, posY, pixelSize);
}
} // namespace katze
