#ifndef KATZE_ICONS_HPP
#define KATZE_ICONS_HPP

/**
 * katze renders its icons using an array of bits, with a set bit indicating a
 * filled pixel. Much of this was based on raygui's implementation!
 */

#include <array>
#include <cstdint>

#define KATZE_U32_BIT_SIZE sizeof(uint32_t) * 8

// Length of a row or column of a katze icon
#define KATZE_ICON_SIZE 16

// Total number of bits required for a katze icon
#define KATZE_ICON_BIT_SIZE KATZE_ICON_SIZE *KATZE_ICON_SIZE

// Number of 32-bit items needed to represent a katze icon
#define KATZE_ICON_ITEM_COUNT (KATZE_ICON_BIT_SIZE) / (KATZE_U32_BIT_SIZE)

#define KATZE_ICON_MAX_ICONS 256

struct SDL_Renderer;

namespace katze {
using IconBits = std::array<uint32_t, KATZE_ICON_ITEM_COUNT>;
using IconSet =
  std::array<uint32_t, KATZE_ICON_ITEM_COUNT * KATZE_ICON_MAX_ICONS>;

IconBits iconBitsById(uint8_t iconId, const IconSet &iconSet);

void drawIcon(
  SDL_Renderer *rend,
  const IconBits &iconBits,
  float posX,
  float posY,
  float pixelSize
);

void drawIcon(
  SDL_Renderer *rend,
  uint8_t iconId,
  const IconSet &iconSet,
  float posX,
  float posY,
  float pixelSize
);
} // namespace katze

#endif // !KATZE_ICONS_HPP
