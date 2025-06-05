#pragma once
#include "katzen.hpp"
#include <raylib.h>

struct Gctx {
  Vector2 p;
  Vector2 bounds;
};

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
