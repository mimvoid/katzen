#ifndef KATZE_TEXT_FONT_HPP
#define KATZE_TEXT_FONT_HPP

#include <cstdint>

struct TTF_Font;

namespace katze {
namespace FontStyle {
enum FontStyle : uint8_t {
  NORMAL = 0,
  BOLD = 1,
  ITALIC = 2,
  UNDERLINE = 4,
  STRIKETHROUGH = 8,
};
}

namespace FontWeight {
enum FontWeight : int {
  THIN = 100,
  EXTRA_LIGHT = 200,
  LIGHT = 300,
  NORMAL = 400,
  MEDIUM = 500,
  SEMI_BOLD = 600,
  BOLD = 700,
  EXTRA_BOLD = 800,
  BLACK = 900,
  EXTRA_BLACK = 950,
};
}

enum class FontDirection : uint8_t {
  INVALID,
  LTR, // left to right
  RTL, // right to left
  TTB, // top to bottom
  BTT, // bottom to top
};

enum class FontHinting : uint8_t {
  INVALID,
  NORMAL,
  LIGHT,
  MONO,
  NONE,
  LIGHT_SUBPIXEL,
};

struct Font {
  TTF_Font *data{nullptr};

  Font() = default;
  Font(TTF_Font *font) : data(font) {}
  Font(const char *filePath, float pointSize);

  void close();

  const char *familyName() const;
  int weight() const;
  bool fixedWidth() const;
  bool scalable() const;

  bool hasGlyph(uint32_t codepoint) const;

  bool kerning() const;
  void setKerning(bool enabled);

  float size() const;
  bool setSize(float pointSize);

  uint8_t style() const;
  void setStyle(uint8_t styleFlags);

  int lineSkip() const;
  void setLineSkip(int lineSkip);

  FontDirection direction() const;
  bool setDirection(FontDirection dir);

  FontHinting hinting() const;
  void setHinting(FontHinting value);
};
} // namespace katze

#endif // !KATZE_TEXT_FONT_HPP
