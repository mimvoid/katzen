#include "Gctx.hpp"

Gctx NewGctx() {
  Gctx g{};
  ResetGctx(g);
  return g;
}

Gctx NewGctx(float padTop, float padRight, float padBottom, float padLeft) {
  Gctx g{};
  ResetGctx(g, padTop, padRight, padBottom, padLeft);
  return g;
}

Gctx NewGctx(float padY, float padX) {
  Gctx g{};
  ResetGctx(g, padY, padX);
  return g;
}

Gctx NewGctx(float pad) {
  Gctx g{};
  ResetGctx(g, pad);
  return g;
}

void ResetGctx(Gctx &g) {
  g.p.x = 0;
  g.p.y = 0;

  g.bounds.x = GetRenderWidth();
  g.bounds.y = GetRenderHeight();
}

void ResetGctx(
    Gctx &g, float padTop, float padRight, float padBottom, float padLeft) {
  ResetGctx(g);
  PadGctx(g, padTop, padRight, padBottom, padLeft);
}

void ResetGctx(Gctx &g, float padY, float padX) {
  ResetGctx(g);
  PadGctx(g, padY, padX);
}

void ResetGctx(Gctx &g, float pad) {
  ResetGctx(g);
  PadGctx(g, pad);
}

void PositionGctx(Gctx &g, Axis a, float p) {
  switch (a) {
    case Axis::X:
      g.p.x = p;
      break;
    case Axis::Y:
      g.p.y = p;
      break;
  }
}

void TranslateGctx(Gctx &g, Axis a, float p) {
  switch (a) {
    case Axis::X:
      g.p.x += p;
      break;
    case Axis::Y:
      g.p.y += p;
      break;
  }
}

void TranslateClipGctx(Gctx &g, Axis a, float p) {
  switch (a) {
    case Axis::X:
      g.p.x += p;
      g.bounds.x -= p;
      break;
    case Axis::Y:
      g.p.y += p;
      g.bounds.y -= p;
      break;
  }
}

void TranslateClipGctx(Gctx &g, float x, float y) {
  g.p.x += x;
  g.bounds.x -= x;
  g.p.y += y;
  g.bounds.y -= y;
}

void PadGctx(Gctx &g, int padTop, int padRight, int padBottom, int padLeft) {
  g.p.x += padLeft;
  g.p.y += padTop;

  g.bounds.x -= padLeft + padRight;
  g.bounds.y -= padTop + padBottom;
}

void PadGctx(Gctx &g, int padY, int padX) {
  g.p.x += padX;
  g.p.y += padY;

  g.bounds.x -= padX * 2;
  g.bounds.y -= padY * 2;
}

void PadGctx(Gctx &g, int pad) {
  g.p.x += pad;
  g.p.y += pad;

  g.bounds.x -= pad * 2;
  g.bounds.y -= pad * 2;
}
