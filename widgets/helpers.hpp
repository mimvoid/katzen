#pragma once
#include <raylib.h>

void DrawTextBoxed(const Font &font,
                   const char *text,
                   const Rectangle &rec,
                   float fontSize,
                   float spacing,
                   Color tint);
