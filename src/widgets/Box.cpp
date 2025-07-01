#include "Box.hpp"
#include "../core/vectors.hpp"

namespace katzen {
Box::Box(int spacing,
         Axis direction,
         Align halign,
         Align valign,
         std::function<void(Box &)> setup)
    : spacing(spacing), direction(direction), halign(halign), valign(valign) {
  if (setup) setup(*this);
}

Vec2 Box::remeasureChildren() {
  if (children.empty()) return {0.0f, 0.0f};

  float dirSize = 0.0f;
  float flipDirSize = 0.0f;

  const std::size_t childrenCount = children.size();
  dirSize += spacing * (childrenCount - 1);

  std::vector<Widget *> expandedChildren;
  expandedChildren.reserve(childrenCount);

  const Axis flipDir = flip(direction);
  float maxChildSize = 0.0f;

  const unsigned int maxDir = maxSize(direction) - padding.get(direction);
  const unsigned int maxFlipDir = maxSize(flipDir) - padding.get(flipDir);

  for (value_type &w : children) {
    // Box direction
    if (get(w->expand, direction)) {
      expandedChildren.push_back(w.get());
    } else {
      set(w->m_externalBounds,
          direction,
          static_cast<unsigned int>(maxDir - dirSize));
      w->resize(direction);
      dirSize += w->size(direction);
    }

    // Flipped direction
    set(w->m_externalBounds, flipDir, maxFlipDir);
    w->resize(flipDir);
    maxChildSize = std::max(w->size(flipDir), maxChildSize);
  }

  flipDirSize += maxChildSize;

  if (!expandedChildren.empty()) {
    const unsigned int expandedSize =
        std::max(0.0f, maxSize(direction) - padding.get(direction) - dirSize)
        / expandedChildren.size();

    for (Widget *w : expandedChildren) {
      set(w->m_externalBounds, direction, expandedSize);
      w->resize(direction);
      dirSize += w->size(direction);
    }
  }

  if (direction == Axis::X) {
    return {dirSize, flipDirSize};
  }
  return {flipDirSize, dirSize};
}

float Box::measureChildren(Axis axis) const {
  if (children.empty()) return 0.0f;

  if (axis == direction) {
    float childrenSize = spacing * (children.size() - 1);

    for (const value_type &w : children) {
      if (get(w->expand, axis)) return maxSize(axis) - padding.get(axis);
      childrenSize += w->size(axis);
    }

    return childrenSize;
  }

  float maxChildSize = 0.0f;

  for (const value_type &w : children) {
    if (get(w->expand, axis)) return maxSize(axis) - padding.get(axis);
    maxChildSize = std::max(w->size(axis), maxChildSize);
  }

  return maxChildSize;
}

float Box::measure(Axis axis) const {
  const float size = padding.get(axis) + measureChildren(axis);
  return clampSize(size, axis);
}

void Box::repaint(Gctx g) {
  setExternalBounds(g);
  reposition(g);

  Vec2 cSize = remeasureChildren();
  m_rect.w = clampSize(cSize.x + padding.get(Axis::X), Axis::X);
  m_rect.h = clampSize(cSize.y + padding.get(Axis::Y), Axis::Y);

  if (children.empty()) {
    return;
  }

  g.pad(padding);

  if (get(expand, direction)) {
    const Align dirAlign = align(direction);

    if (dirAlign != Align::START) {
      const float sizeDiff = offset(size(direction) - padding.get(direction),
                                    get(cSize, direction),
                                    dirAlign);

      g.translateClip(direction, sizeDiff);
    }
  }

  const Axis flipDir = flip(direction);
  const Align flipAlign = align(flipDir);

  const Axis dirCopy = direction;
  const auto repaintChild = [dirCopy](Widget &w, Gctx &gctx) {
    if (get(w.expand, dirCopy)) {
      const unsigned int prevSize = std::max(0.0f, w.size(dirCopy));
      w.repaint(gctx);
      set(w.m_externalBounds, dirCopy, prevSize);
      w.resize(dirCopy);
    } else {
      w.repaint(gctx);
    }
  };

  for (auto i = children.begin(); i != children.end(); i++) {
    if (i != children.begin()) {
      g.translateClip(direction, spacing);
    }

    Widget &w = *i.base()->get();

    if (flipAlign == Align::START || get(w.expand, flipDir)) {
      repaintChild(w, g);
    } else {
      const float sizeDiff =
          size(flipDir) - padding.get(flipDir) - w.size(flipDir);

      if (sizeDiff <= 0.0f) {
        repaintChild(w, g);
      } else {
        Gctx gCopy = g;
        gCopy.translateClip(
            flipDir,
            (flipAlign == Align::CENTER) ? (sizeDiff / 2.0f) : sizeDiff);

        repaintChild(w, gCopy);
      }
    }

    g.translateClip(direction, w.size(direction));
  }
}

void Box::draw(Dctx &d) {
  const State savedState = d.state;
  const StateColors savedColors = d.colors;

  for (value_type &w : children) {
    w->draw(d);

    // Reset
    d.state = savedState;
    d.colors = savedColors;
  }
}
} // namespace katzen
