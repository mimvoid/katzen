#pragma once
#include <raylib.h>

struct Point {
  int x;
  int y;
};

struct Bounds {
  Point min;
  Point max;
};

struct Gctx {
  Vector2 p;
  Vector2 bounds;
};

enum class Align { START, CENTER, END };
enum class Axis { X, Y };

static constexpr Axis flipAxis(Axis a) {
  switch (a) {
    case Axis::X:
      return Axis::Y;
    case Axis::Y:
      return Axis::X;
  }
}

static constexpr float VectorAxisValue(Vector2 vector, Axis a) {
  switch (a) {
    case Axis::X:
      return vector.x;
    case Axis::Y:
      return vector.y;
  }
}

struct Edges {
  int top;
  int right;
  int bottom;
  int left;
};

enum class Edge { TOP, RIGHT, BOTTOM, LEFT };

constexpr int GetEdgeValue(const Edges edges, const Edge targetEdge) {
  switch (targetEdge) {
    case Edge::TOP:
      return edges.top;
    case Edge::RIGHT:
      return edges.right;
    case Edge::BOTTOM:
      return edges.bottom;
    case Edge::LEFT:
      return edges.left;
  }
}

constexpr void
SetEdgeValue(Edges &edges, const Edge targetEdge, const int value) {
  switch (targetEdge) {
    case Edge::TOP:
      edges.top = value;
      break;
    case Edge::RIGHT:
      edges.right = value;
      break;
    case Edge::BOTTOM:
      edges.bottom = value;
      break;
    case Edge::LEFT:
      edges.left = value;
      break;
  }
}

Gctx NewGctx();
Gctx NewGctx(float pad);
Gctx NewGctx(float padY, float padX);
Gctx NewGctx(float padTop, float padRight, float padBottom, float padLeft);

void ResetGctx(Gctx &g);
void ResetGctx(Gctx &g, float pad);
void ResetGctx(Gctx &g, float padY, float padX);
void ResetGctx(
    Gctx &g, float padTop, float padRight, float padBottom, float padLeft);

void PositionGctx(Gctx &g, Axis a, float p);
void TranslateGctx(Gctx &g, Axis a, float p);
void TranslateClipGctx(Gctx &g, Axis a, float p);
void TranslateClipGctx(Gctx &g, float x, float y);

void PadGctx(Gctx &g, int pad);
void PadGctx(Gctx &g, int padY, int padX);
void PadGctx(Gctx &g, int padTop, int padRight, int padBottom, int padLeft);
