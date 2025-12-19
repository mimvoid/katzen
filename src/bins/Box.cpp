#include "bins/Box.hpp"
#include "ctx/Dctx.hpp"

namespace katze {
void Box::view(Dctx &d, [[maybe_unused]] FRect rect) {
  for (size_t i = 0; i < m_children.size(); i++) {
    std::shared_ptr<Widget> &w = m_children[i];

    if (w) {
      State savedState = d.state;
      w->view(d, m_childRects[i]);
      d.state = savedState; // reset
    }
  }
}

void Box::resize(Gctx g, FRect &rect) {
  const float childCount = m_children.size();
  if (childCount == 0) {
    // No children to measure, set size to 0
    rect.w = 0;
    rect.h = 0;
    return;
  }

  // Measure children sizes
  Gctx gCopy = g;
  const FVec2 cSize = resizeChildren(gCopy);

  // Update box size
  rect.w = g.clampWidth(cSize.x);
  rect.h = g.clampHeight(cSize.y);
}

float Box::measureChildren(float bound) const {
  float size = 0.0f;

  for (size_t i = 0; i < m_children.size(); i++) {
    if (m_expanded[i]) {
      return bound;
    }
    size += m_childRects[i].size(direction);
  }

  return size;
}

FVec2 Box::resizeChildren(Gctx g) {
  const size_t childCount = m_children.size();
  if (childCount == 0) {
    return {0.0f, 0.0f};
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
  std::vector<size_t> expandedIdx{};
  expandedIdx.reserve(childCount);

  // Measure children
  for (size_t i = 0; i < childCount; i++) {
    std::shared_ptr<Widget> &w = m_children[i];
    FRect &wRect = m_childRects[i];

    if (m_expanded[i]) {
      expandedIdx.push_back(i);
      continue;
    }

    g.setSize(direction, dirBound - dirSize);
    w->resize(g, wRect);

    dirSize += wRect.size(direction);
    flipDirSize = std::max(wRect.size(flipDir), flipDirSize);
  }

  // Remeasure expanded children
  if (!expandedIdx.empty()) {
    m_expandedSize = (dirBound - dirSize) / expandedIdx.size();
    dirSize = dirBound;
    g.setSize(direction, m_expandedSize);

    for (size_t i : expandedIdx) {
      // Resize to properly measure the child
      FRect &wRect = m_childRects[i];
      m_children[i]->resize(g, wRect);
      flipDirSize = std::max(wRect.size(flipDir), flipDirSize);
    }
  }

  return (direction == Axis::X) ? FVec2{dirSize, flipDirSize}
                                : FVec2{flipDirSize, dirSize};
}

void Box::repositionChildren(FRect rect) {
  const float dirBound = rect.size(direction);
  const float dirOffset =
    offset(dirBound, measureChildren(dirBound), align.get(direction));

  if (direction == Axis::X)
    rect.x += dirOffset;
  else
    rect.y += dirOffset;

  const Axis flipDir = flip(direction);
  const float flipBound = rect.size(flipDir);

  for (size_t i = 0; i < m_children.size(); i++) {
    std::shared_ptr<Widget> &w = m_children[i];
    FRect &wRect = m_childRects[i];

    const float flipOffset =
      offset(flipBound, wRect.size(flipDir), align.get(flipDir));

    float childSize = wRect.size(direction);
    float innerOffset = 0.0f;

    if (m_expanded[i]) {
      innerOffset = offset(m_expandedSize, childSize, align.get(direction));
      childSize = m_expandedSize;
    }

    if (direction == Axis::X) {
      w->reposition({rect.x + innerOffset, rect.y + flipOffset}, wRect);
      rect.x += childSize + spacing;
    } else {
      w->reposition({rect.x + flipOffset, rect.y + innerOffset}, wRect);
      rect.y += childSize + spacing;
    }
  }
}
} // namespace katze
