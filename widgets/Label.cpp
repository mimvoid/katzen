#include "../widgets.hpp"
#include "helpers.hpp"
#include <algorithm>
#include <cmath>

Label::Label(const Font &font, const char *text) : font(font), fontSize(24) {
  init(text);
}
Label::Label(const Font &font, const char *text, float size)
    : font(font), fontSize(size) {
  init(text);
}

void Label::init(const char *text) {
  wrapWords = true;
  color = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
  fontSpacing = GuiGetStyle(DEFAULT, TEXT_SPACING);
  setText(text);
}

const char *Label::getText() const { return this->text; }
void Label::setText(const char *text) {
  this->text = (text == NULL) ? "" : text;
}

bool Label::isEmpty() const { return !text || !text[0]; }

float Label::measureText(Axis a) const {
  if (isEmpty()) {
    return 0;
  }

  const Vector2 textSize =
      MeasureTextEx(this->font, this->text, this->fontSize, fontSpacing);

  return a == Axis::X ? textSize.x : textSize.y;
}
float Label::measureTextWidth() const { return measureText(Axis::X); }
float Label::measureTextHeight() const { return measureText(Axis::Y); }

bool Label::willWrap() const {
  return wrapWords && (measureTextWidth() + getTotalPaddingX() > getMaxWidth());
}

float Label::measureSize(Axis a) const {
  float labelSize = getTotalPadding(a);

  if (a == Axis::X || !willWrap()) {
    labelSize += measureText(a);
  } else {
    // Estimate the height after text wrapping
    // It's not perfect, but it's simple
    const int lines =
        std::ceil(measureTextWidth() / (getMaxWidth() - getTotalPaddingX()));
    labelSize += measureText(a) * lines;
  }

  return std::clamp(labelSize, (float)getMinSize(a), (float)getMaxSize(a));
}

void Label::draw(Vector2 p) {
  if (isEmpty()) {
    return;
  }

  p.x += padding.left;
  p.y += padding.top;

  if (willWrap()) {
    DrawTextBoxed(font,
                  text,
                  {p.x,
                   p.y,
                   getWidth() - getTotalPaddingX(),
                   getHeight() - getTotalPaddingY()},
                  fontSize,
                  fontSpacing,
                  color);
  } else {
    DrawTextEx(font, text, p, fontSize, fontSpacing, color);
  }
}
