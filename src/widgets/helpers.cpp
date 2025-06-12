#include "helpers.hpp"
#include <utility>

/*
 * Raylib example: rectangle bounds
 */

// Draw text using font inside rectangle limits
void drawTextBoxed(const Font &font,
                   const char *text,
                   const Rectangle &rec,
                   float fontSize,
                   float spacing,
                   Color tint) {
  // Total length in bytes of the text, scanned by codepoints in loop
  const int length = TextLength(text);

  float textOffsetX = 0; // offset to next character to draw
  float textOffsetY = 0; // offset between lines (on line break '\n')

  // Character rectangle scaling factor
  const float scaleFactor = fontSize / font.baseSize;
  const int lineHeight = fontSize;

  // Word/character wrapping mechanism variables
  enum { MEASURE_STATE, DRAW_STATE };
  int state = MEASURE_STATE;

  int startLine = -1; // Index where to begin drawing (where a line begins)
  int endLine = -1;   // Index where to stop drawing (where a line ends)
  int lastk = -1;     // Holds last value of the character position

  for (int i = 0, k = 0; i < length; i++, k++) {
    // Get next codepoint from byte string and glyph index in font
    int codepointByteCount = 0;
    int codepoint = GetCodepoint(&text[i], &codepointByteCount);
    const int index = GetGlyphIndex(font, codepoint);

    // NOTE: Normally we exit the decoding sequence as soon as a bad byte is
    // found (and return 0x3f) but we need to draw all of the bad bytes using
    // the '?' symbol moving one byte
    if (codepoint != 0x3f) codepointByteCount = 1;

    i += (codepointByteCount - 1);

    float glyphWidth = 0;
    if (codepoint != '\n') {
      int glyphAdvanceX = font.glyphs[index].advanceX;
      glyphWidth =
          scaleFactor
          * (glyphAdvanceX == 0 ? font.recs[index].width : glyphAdvanceX);

      if (i + 1 < length) glyphWidth += spacing;
    }

    /**
     * NOTE: When wordWrap is ON we first measure how much of the text we can
     * draw before going outside of the rec container.
     *
     * We store this info in startLine and endLine, then we change states, draw
     * the text between those two variables and change states again and again
     * recursively until the end of the text (or until we get outside of the
     * container).
     *
     * When wordWrap is OFF we don't need the measure state so we go
     * to the drawing state immediately and begin drawing on the next line
     * before we can get outside the container.
     */
    if (state == MEASURE_STATE) {
      if (isWhitespaceCharacter(codepoint)) endLine = i;

      const bool overflowing = (textOffsetX + glyphWidth) > rec.width;
      const bool endOfText = (i + 1) == length;

      if (overflowing) {
        if (endLine < 1) endLine = i;

        if (i == endLine) endLine -= codepointByteCount;

        if ((startLine + codepointByteCount) == endLine)
          endLine = (i - codepointByteCount);
      } else if (endOfText) {
        endLine = i;
      }

      if (overflowing || endOfText || codepoint == '\n') {
        state = DRAW_STATE;

        textOffsetX = 0;
        i = startLine;
        glyphWidth = 0;

        // Save character position when we switch states
        std::swap(k, lastk);
        lastk--;
      }
    } else {
      // Draw current character glyph if:
      // 1. The text is not overflowing the rectangle height limit
      // 2. It is not a whitespace character
      if (!(textOffsetY + lineHeight > rec.height)
          && !isWhitespaceCharacter(codepoint)) {
        DrawTextCodepoint(font,
                          codepoint,
                          {rec.x + textOffsetX, rec.y + textOffsetY},
                          fontSize,
                          tint);
      }

      if (i == endLine) {
        textOffsetY += lineHeight;
        textOffsetX = 0;
        startLine = endLine;
        endLine = -1;
        glyphWidth = 0;
        k = lastk;

        state = MEASURE_STATE;
      }
    }

    if (textOffsetX != 0 || codepoint != ' ')
      textOffsetX += glyphWidth; // avoid leading spaces
  }
}
