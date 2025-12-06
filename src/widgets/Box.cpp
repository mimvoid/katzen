#include "widgets/Box.hpp"
#include "core/vectors.hpp"

namespace katzen {
Vec2 Box::resizeChildren(Gctx g) {
  const size_type childCount = m_children.size();
  if (childCount == 0) {
    return Vec2{0.0f, 0.0f};
  }

  // Save information for use later
  const float dirBound = g.size(direction);
  const Axis flipDir = flip(direction);

  // Size of the children in the Box's direction
  float dirSize = spacing * (childCount - 1);

  // Size of the children in the opposite of the Box's direction
  float flipDirSize = 0.0f;

  // Expanded widgets are variable in size, so we'll remeasure them after other
  // children have been measured
  std::vector<Widget *> expandedChildren{};
  expandedChildren.reserve(childCount);

  // Measure children
  for (value_type &w : m_children) {
    if (w->expand.get(direction)) {
      expandedChildren.push_back(w.get());
      continue;
    }

    g.setSize(direction, dirBound - dirSize);
    w->resize(g);

    dirSize += w->size(direction);
    flipDirSize = std::max(w->size(flipDir), flipDirSize);
  }

  // Remeasure expanded children
  if (const size_t expCount = expandedChildren.size(); expCount != 0) {
    m_expandedSize = (dirBound - dirSize) / expCount;
    dirSize = dirBound;
    g.setSize(direction, m_expandedSize);

    for (Widget *w : expandedChildren) {
      // Resize to properly measure the child
      w->resize(g);
      flipDirSize = std::max(w->size(flipDir), flipDirSize);
    }
  }

  return (direction == Axis::X) ? Vec2{dirSize, flipDirSize}
                                : Vec2{flipDirSize, dirSize};
}

void Box::reposition(Vec2 position) {
  Widget::reposition(position);

  const Axis flipDir = flip(direction);
  const Align dirAlign = align.get(direction);

  const float dirBound = size(direction) - padding.getSum(direction);
  const float flipBound = size(flipDir) - padding.getSum(flipDir);

  float childrenDirSize = 0.0f;
  for (value_type &w : m_children) {
    if (w->expand.get(direction)) {
      childrenDirSize = dirBound;
      break;
    }
    childrenDirSize += w->size(direction);
  }

  position.x += padding.left;
  position.y += padding.top;
  position.set(
    direction,
    position.get(direction) + offset(dirBound, childrenDirSize, dirAlign)
  );

  // Position each child
  for (value_type &w : m_children) {
    const float flipOffset =
      offset(flipBound, w->size(flipDir), align.get(flipDir));

    float childSize = w->size(direction);
    float dirOffset = 0.0f;

    if (dirAlign != Align::START && w->expand.get(direction)) {
      dirOffset = offset(m_expandedSize, childSize, dirAlign);
      childSize = m_expandedSize;
    }

    if (direction == Axis::X) {
      w->reposition(Vec2{position.x + dirOffset, position.y + flipOffset});
      position.x += childSize + spacing;
    } else {
      w->reposition(Vec2{position.x + flipOffset, position.y + dirOffset});
      position.y += childSize + spacing;
    }
  }
}

void Box::resize(Gctx g) {
  const float childCount = m_children.size();
  if (childCount == 0) {
    // No children to measure, just resize based on padding
    Widget::resize(g);
    return;
  }

  // Measure children sizes
  Gctx gCopy = g;
  gCopy.pad(padding);
  const Vec2 cSize = resizeChildren(gCopy);

  // Update box size
  m_rect.w = g.clampWidth(cSize.x + padding.getX());
  m_rect.h = g.clampHeight(cSize.y + padding.getY());
}

void Box::draw(Dctx &d) {
  const State savedState = d.state;

  for (value_type &w : m_children) {
    w->draw(d);
    d.state = savedState; // reset
  }
}
} // namespace katzen
