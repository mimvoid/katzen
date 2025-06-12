#pragma once
#include <raylib.h>

constexpr bool isWhitespaceCharacter(int codepoint) {
  const char wsChars[]{' ', '\t', '\n', '\f', '\r', '\v'};

  for (char chara : wsChars) {
    if (codepoint == chara) return true;
  }

  return false;
}

void drawTextBoxed(const Font &font,
                   const char *text,
                   const Rectangle &rec,
                   float fontSize,
                   float spacing,
                   Color tint);
