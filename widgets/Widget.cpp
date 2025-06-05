#include "../widgets.hpp"
#include <algorithm>
#include <climits>

Widget::Widget()
    : hexpand(false), vexpand(false), padding{0, 0, 0, 0},
      internalBounds{{0, 0}, {INT_MAX, INT_MAX}},
      externalBounds{GetRenderWidth(), GetRenderHeight()} {}

Rectangle Widget::getBox() const { return box; }

float Widget::getX() const { return box.x; }
float Widget::getY() const { return box.y; }
Vector2 Widget::getPosition() const { return {box.x, box.y}; }

void Widget::setPosition(Vector2 p) {
  box.x = p.x;
  box.y = p.y;
}

float Widget::getWidth() const { return box.width; }
float Widget::getHeight() const { return box.height; }
float Widget::getSize(Axis a) const {
  switch (a) {
    case Axis::X:
      return box.width;
    case Axis::Y:
      return box.height;
  }
}

int Widget::getMinWidth() const { return internalBounds.min.x; }
int Widget::getMinHeight() const { return internalBounds.min.y; }
int Widget::getMinSize(Axis a) const {
  switch (a) {
    case Axis::X:
      return getMinWidth();
    case Axis::Y:
      return getMinHeight();
  }
}

int Widget::getMaxWidth() const {
  return std::max(internalBounds.min.x,
                  std::min(internalBounds.max.x, externalBounds.x));
}
int Widget::getMaxHeight() const {
  return std::max(internalBounds.min.y,
                  std::min(internalBounds.max.y, externalBounds.y));
}
int Widget::getMaxSize(Axis a) const {
  switch (a) {
    case Axis::X:
      return getMaxWidth();
    case Axis::Y:
      return getMaxHeight();
  }
}

bool Widget::expands(Axis a) const {
  switch (a) {
    case Axis::X:
      return hexpand;
    case Axis::Y:
      return vexpand;
  }
}

void Widget::setMinWidth(int minW) {
  if (minW > getMaxWidth()) {
    setMaxWidth(minW);
  }
  internalBounds.min.x = minW;
}
void Widget::setMinHeight(int minH) {
  if (minH > getMaxHeight()) {
    setMaxHeight(minH);
  }
  internalBounds.min.y = minH;
}
void Widget::setMinSize(int minW, int minH) {
  setMinWidth(minW);
  setMinHeight(minH);
}

void Widget::setMaxWidth(int maxW) {
  if (maxW < getMinWidth()) {
    setMinWidth(maxW);
  }
  internalBounds.max.x = maxW;
}
void Widget::setMaxHeight(int maxH) {
  if (maxH < getMinHeight()) {
    setMinHeight(maxH);
  }
  internalBounds.max.y = maxH;
}
void Widget::setMaxSize(int maxW, int maxH) {
  setMaxWidth(maxW);
  setMaxHeight(maxH);
}

void Widget::setExternalBound(float bound, Axis a) {
  switch (a) {
    case Axis::X:
      externalBounds.x = std::max(bound, 0.0f);
      break;
    case Axis::Y:
      externalBounds.y = std::max(bound, 0.0f);
      break;
  }
}
void Widget::setExternalBounds(Vector2 bounds) {
  externalBounds.x = std::max(bounds.x, 0.0f);
  externalBounds.y = std::max(bounds.y, 0.0f);
}

int Widget::getPaddingEdge(Edge edge) const {
  return GetEdgeValue(padding, edge);
}
Edges Widget::getPadding() const { return padding; }

int Widget::getTotalPaddingX() const { return padding.right + padding.left; }
int Widget::getTotalPaddingY() const { return padding.top + padding.bottom; }
int Widget::getTotalPadding(Axis a) const {
  switch (a) {
    case Axis::X:
      return getTotalPaddingX();
    case Axis::Y:
      return getTotalPaddingY();
  }
}

void Widget::setPadding(Edge edge, int value) {
  SetEdgeValue(padding, edge, value);
}

void Widget::setPadding(int padTop, int padRight, int padBottom, int padLeft) {
  padding.top = std::max(padTop, 0);
  padding.right = std::max(padRight, 0);
  padding.bottom = std::max(padBottom, 0);
  padding.left = std::max(padLeft, 0);
}
void Widget::setPadding(int padY, int padX) {
  setPadding(padY, padX, padY, padX);
}
void Widget::setPadding(int pad) { setPadding(pad, pad, pad, pad); }

void Widget::pad(Gctx &g) const {
  PadGctx(g, padding.top, padding.right, padding.bottom, padding.left);
}

void Widget::draw() {
#if (defined(DEBUG) && DEBUG)
  DrawRectangleLinesEx(getBox(), 1, RED);
#endif

  draw(getPosition());
}

float Widget::measureWidth() const {
  return hexpand ? getMaxWidth() : measureSize(Axis::X);
}
float Widget::measureHeight() const {
  return vexpand ? getMaxHeight() : measureSize(Axis::Y);
}

void Widget::updateWidth() { box.width = measureWidth(); }
void Widget::updateHeight() { box.height = measureHeight(); }
void Widget::updateSize(Axis a) {
  switch (a) {
    case Axis::X:
      updateWidth();
      break;
    case Axis::Y:
      updateHeight();
      break;
  }
}

void Widget::repaint(Gctx g) {
  setExternalBounds(g.bounds);
  setPosition(g.p);

  updateWidth();
  updateHeight();
}
