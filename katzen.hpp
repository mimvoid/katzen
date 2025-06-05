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
