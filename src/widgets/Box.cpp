#include "widgets/Box.hpp"
#include "core/vectors.hpp"

namespace katzen {
void Box::translate(float dx, float dy) {
  Widget::translate(dx, dy);
  translateChildren(dx, dy);
}

Vec2 Box::remeasureChildren(Gctx g) {
  const size_type childrenSize = m_children.size();
  if (childrenSize == 0) {
    return Vec2{0.0f, 0.0f};
  }

  // Save information for use later
  const float dirBound = (direction == Axis::X) ? g.w : g.h;
  const Axis flipDir = flip(direction);

  // Size of the children in the Box's direction
  float dirSize = spacing * (childrenSize - 1);

  // Size of the children in the opposite of the Box's direction
  float flipDirSize = 0.0f;

  // Expanded widgets are variable in size, so we'll remeasure them after other
  // children have been measured
  std::vector<Widget *> expandedChildren{};
  expandedChildren.reserve(childrenSize);

  // Measure children
  for (value_type &w : m_children) {
    Gctx gCopy = g;
    gCopy.clip(direction, dirSize);
    w->repaint(gCopy);

    if (w->expand.get(direction)) {
      expandedChildren.push_back(w.get());
    } else {
      dirSize += w->size(direction);
    }

    flipDirSize = std::max(w->size(flipDir), flipDirSize);
  }

  // Remeasure expanded children
  if (const size_t expCount = expandedChildren.size(); expCount != 0) {
    const unsigned int expandedSize =
        std::max(0.0f, dirBound - dirSize) / expCount;

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

void Box::positionChildren(Vec2 childrenSize) {
  const Axis flipDir = flip(direction);
  const Align dirAlign = align(direction);
  const Align flipAlign = align(flipDir);

  const float parentFlip = size(flipDir) - padding.getSum(flipDir);

  float dirOffset = offset(size(direction) - padding.getSum(direction),
                           childrenSize.get(direction),
                           dirAlign);

  bool isFirst = true; // the first widget won't start with spacing

  // Position each child
  for (value_type &w : m_children) {
    if (isFirst) {
      isFirst = false;
    } else {
      dirOffset += spacing;
    }

    const float flipOffset = offset(parentFlip, w->size(flipDir), flipAlign);

    float innerOffset = 0.0f;
    if (dirAlign != Align::START && w->expand.get(direction)) {
      innerOffset = offset(w->size(direction), w->measure(direction), dirAlign);
    }

    if (direction == Axis::X) {
      w->translate(dirOffset + innerOffset, flipOffset);
    } else {
      w->translate(flipOffset, dirOffset + innerOffset);
    }

    dirOffset += w->size(direction);
  }
}

void Box::repaint(Gctx &g) {
  setBounds(g);
  reposition(g);

  const float childCount = m_children.size();
  if (childCount == 0) {
    // No children to measure, just resize based on padding
    m_rect.w = clampSize(padding.getSum(Axis::X), Axis::X);
    m_rect.h = clampSize(padding.getSum(Axis::Y), Axis::Y);
    return;
  }

  // Measure children sizes
  g.pad(padding);
  const Vec2 cSize = remeasureChildren(g);

  // Update box size
  m_rect.w = clampSize(cSize.x + padding.getSum(Axis::X), Axis::X);
  m_rect.h = clampSize(cSize.y + padding.getSum(Axis::Y), Axis::Y);

  // Position children after their sizes are known
  positionChildren(cSize);
}

void Box::draw(Dctx &d) {
  const State savedState = d.state;

  for (value_type &w : m_children) {
    w->draw(d);
    d.state = savedState; // reset
  }
}
} // namespace katzen
