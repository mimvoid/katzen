#include "Font.hpp"
#include <SDL3_ttf/SDL_ttf.h>

namespace katze {
FontDirection fromTTFDir(TTF_Direction from) {
  switch (from) {
  case TTF_DIRECTION_LTR: return FontDirection::LTR;
  case TTF_DIRECTION_RTL: return FontDirection::RTL;
  case TTF_DIRECTION_TTB: return FontDirection::TTB;
  case TTF_DIRECTION_BTT: return FontDirection::BTT;
  default:                return FontDirection::INVALID;
  }
}
TTF_Direction toTTFDir(FontDirection from) {
  switch (from) {
  case FontDirection::LTR: return TTF_DIRECTION_LTR;
  case FontDirection::RTL: return TTF_DIRECTION_RTL;
  case FontDirection::TTB: return TTF_DIRECTION_TTB;
  case FontDirection::BTT: return TTF_DIRECTION_BTT;
  default:                 return TTF_DIRECTION_INVALID;
  }
}

FontHinting fromTTFHinting(TTF_HintingFlags from) {
  switch (from) {
  case TTF_HINTING_NORMAL:         return FontHinting::NORMAL;
  case TTF_HINTING_LIGHT:          return FontHinting::LIGHT;
  case TTF_HINTING_MONO:           return FontHinting::MONO;
  case TTF_HINTING_NONE:           return FontHinting::NONE;
  case TTF_HINTING_LIGHT_SUBPIXEL: return FontHinting::LIGHT_SUBPIXEL;
  default:                         return FontHinting::INVALID;
  }
}
TTF_HintingFlags toTTFHinting(FontHinting from) {
  switch (from) {
  case FontHinting::NORMAL:         return TTF_HINTING_NORMAL;
  case FontHinting::LIGHT:          return TTF_HINTING_LIGHT;
  case FontHinting::MONO:           return TTF_HINTING_MONO;
  case FontHinting::NONE:           return TTF_HINTING_NONE;
  case FontHinting::LIGHT_SUBPIXEL: return TTF_HINTING_LIGHT_SUBPIXEL;
  default:                          return TTF_HINTING_INVALID;
  }
}

Font::Font(const char *filePath, float pointSize)
  : data(TTF_OpenFont(filePath, pointSize)) {}

void Font::close() { TTF_CloseFont(data); }

const char *Font::familyName() const { return TTF_GetFontFamilyName(data); }
int Font::weight() const { return TTF_GetFontWeight(data); }
bool Font::fixedWidth() const { return TTF_FontIsFixedWidth(data); }
bool Font::scalable() const { return TTF_FontIsScalable(data); }

bool Font::hasGlyph(uint32_t codepoint) const {
  return TTF_FontHasGlyph(data, codepoint);
}

bool Font::kerning() const { return TTF_GetFontKerning(data); }
void Font::setKerning(bool enabled) { TTF_SetFontKerning(data, enabled); }

float Font::size() const { return TTF_GetFontSize(data); }
bool Font::setSize(float pointSize) { return TTF_SetFontSize(data, pointSize); }

uint8_t Font::style() const { return TTF_GetFontStyle(data); }
void Font::setStyle(uint8_t styleFlags) { TTF_SetFontStyle(data, styleFlags); }

int Font::lineSkip() const { return TTF_GetFontLineSkip(data); }
void Font::setLineSkip(int lineSkip) { TTF_SetFontLineSkip(data, lineSkip); }

FontDirection Font::direction() const {
  return fromTTFDir(TTF_GetFontDirection(data));
}
bool Font::setDirection(FontDirection dir) {
  return TTF_SetFontDirection(data, toTTFDir(dir));
}

FontHinting Font::hinting() const {
  return fromTTFHinting(TTF_GetFontHinting(data));
}
void Font::setHinting(FontHinting value) {
  TTF_SetFontHinting(data, toTTFHinting(value));
}
} // namespace katze
