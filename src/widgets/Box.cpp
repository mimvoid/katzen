#include "../../include/widgets/Box.hpp"
#include "../../include/core/vectors.hpp"

namespace katzen {
Vec2 Box::remeasureChildren() {
  if (m_children.empty()) return Vec2{0.0f, 0.0f};

  float dirSize = 0.0f;
  float flipDirSize = 0.0f;

  const std::size_t childrenCount = m_children.size();
  dirSize += spacing * (childrenCount - 1);

  std::vector<Widget *> expandedChildren;
  expandedChildren.reserve(childrenCount);

  const Axis flipDir = flip(direction);
  float maxChildSize = 0.0f;

  const unsigned int maxDir =
      m_bounds.get(direction) - padding.getSum(direction);
  const unsigned int maxFlipDir =
      m_bounds.get(flipDir) - padding.getSum(flipDir);

  for (value_type &w : m_children) {
    // Box direction
    if (w->expand.get(direction)) {
      expandedChildren.push_back(w.get());
    } else {
      w->m_bounds.set(direction, static_cast<unsigned int>(maxDir - dirSize));
      w->resize(direction);
      dirSize += w->size(direction);
    }

    // Flipped direction
    w->m_bounds.set(flipDir, maxFlipDir);
    w->resize(flipDir);
    maxChildSize = std::max(w->size(flipDir), maxChildSize);
  }

  flipDirSize += maxChildSize;

  if (!expandedChildren.empty()) {
    const unsigned int expandedSize =
        std::max(0.0f,
                 m_bounds.get(direction) - padding.getSum(direction) - dirSize)
        / expandedChildren.size();

    for (Widget *w : expandedChildren) {
      w->m_bounds.set(direction, expandedSize);
      w->resize(direction);
      dirSize += w->size(direction);
    }
  }

  return (direction == Axis::X) ? Vec2{dirSize, flipDirSize}
                                : Vec2{flipDirSize, dirSize};
}

float Box::measureChildren(Axis axis) const {
  if (m_children.empty()) return 0.0f;

  if (axis == direction) {
    float childrenSize = spacing * (m_children.size() - 1);

    for (const value_type &w : m_children) {
      if (w->expand.get(axis)) return m_bounds.get(axis) - padding.getSum(axis);
      childrenSize += w->size(axis);
    }

    return childrenSize;
  }

  float maxChildSize = 0.0f;

  for (const value_type &w : m_children) {
    if (w->expand.get(axis)) return m_bounds.get(axis) - padding.getSum(axis);
    maxChildSize = std::max(w->size(axis), maxChildSize);
  }

  return maxChildSize;
}

float Box::measure(Axis axis) const {
  const float size = padding.getSum(axis) + measureChildren(axis);
  return clampSize(size, axis);
}

void Box::repaint(Gctx g) {
  setBounds(g);
  reposition(g);

  Vec2 cSize = remeasureChildren();
  m_rect.w = clampSize(cSize.x + padding.getSum(Axis::X), Axis::X);
  m_rect.h = clampSize(cSize.y + padding.getSum(Axis::Y), Axis::Y);

  if (m_children.empty()) {
    return;
  }

  g.pad(padding);

  if (expand.get(direction)) {
    const Align dirAlign = align(direction);

    if (dirAlign != Align::START) {
      const float sizeDiff = offset(size(direction) - padding.getSum(direction),
                                    cSize.get(direction),
                                    dirAlign);

      g.translateClip(direction, sizeDiff);
    }
  }

  const Axis flipDir = flip(direction);
  const Align flipAlign = align(flipDir);

  const Axis dirCopy = direction;
  const auto repaintChild = [dirCopy](Widget &w, Gctx &gctx) {
    if (w.expand.get(dirCopy)) {
      const unsigned int prevSize = std::max(0.0f, w.size(dirCopy));
      w.repaint(gctx);
      w.m_bounds.set(dirCopy, prevSize);
      w.resize(dirCopy);
    } else {
      w.repaint(gctx);
    }
  };

  for (auto i = m_children.begin(); i != m_children.end(); i++) {
    if (i != m_children.begin()) {
      g.translateClip(direction, spacing);
    }

    Widget &w = *i.base()->get();

    if (flipAlign == Align::START || w.expand.get(flipDir)) {
      repaintChild(w, g);
    } else {
      const float sizeDiff =
          size(flipDir) - padding.getSum(flipDir) - w.size(flipDir);

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

  for (value_type &w : m_children) {
    w->draw(d);

    // Reset
    d.state = savedState;
    d.colors = savedColors;
  }
}
} // namespace katzen
