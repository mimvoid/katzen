#pragma once
#include <raylib.h>

namespace katzen {
constexpr bool isWhitespaceCharacter(int codepoint) {
  switch (codepoint) {
  case ' ':
  case '\n':
  case '\t':
  case '\f':
  case '\r':
  case '\v': return true;
  default:   return false;
  }
}

void drawTextBoxed(
  const Font &font,
  const char *text,
  Rectangle rec,
  float fontSize,
  float spacing,
  Color tint
);
} // namespace katzen
