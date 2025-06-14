#include "Box.hpp"

namespace katzen {
float Box::measureChildren(Axis axis) {
  using std::unique_ptr;

  float size = 0.0f;

  if (children.empty()) return size;

  if (axis == direction) {
    const int childrenCount = children.size();
    size += spacing * (childrenCount - 1);

    std::vector<Widget *> expandedChildren;
    expandedChildren.reserve(childrenCount);

    for (unique_ptr<Widget> &w : children) {
      if (get(w->expand, axis)) {
        expandedChildren.push_back(w.get());
      } else {
        set(w->externalBounds,
            axis,
            (unsigned int)glm::max(0.0f,
                                   maxSize(axis) - padding.get(axis) - size));
        w->updateSize(axis);
        size += w->size(axis);
      }
    }

    if (!expandedChildren.empty()) {
      const unsigned int expandedSize =
          glm::max(0.0f, maxSize(axis) - padding.get(axis) - size)
          / expandedChildren.size();

      for (Widget *w : expandedChildren) {
        set(w->externalBounds, axis, expandedSize);
        w->updateSize(axis);
        size += w->size(axis);
      }
    }
  } else {
    float maxChildSize = 0.0f;
    for (unique_ptr<Widget> &w : children) {
      set(w->externalBounds, axis, maxSize(axis));
      w->updateSize(axis);
      maxChildSize = glm::max(w->size(axis), maxChildSize);
    }
    size += maxChildSize;
  }

  return size;
}

float Box::childrenSize(Axis axis) const {
  using std::unique_ptr;

  float size = 0.0f;

  if (!children.empty()) {
    if (axis == direction) {
      size += spacing * (children.size() - 1);

      for (const unique_ptr<Widget> &w : children) {
        if (get(w->expand, axis)) return maxSize(axis) - padding.get(axis);

        size += w->size(axis);
      }
    } else {
      float maxChildSize = 0.0f;
      for (const unique_ptr<Widget> &w : children) {
        if (get(w->expand, axis)) return maxSize(axis) - padding.get(axis);

        maxChildSize = glm::max(w->size(axis), maxChildSize);
      }
      size += maxChildSize;
    }
  }

  return size;
}

float Box::measureSize(Axis axis) const {
  const float size = padding.get(axis) + childrenSize(axis);
  return glm::clamp(size, (float)minSize(axis), (float)maxSize(axis));
}

void Box::repaint(Gctx g) {
  using std::unique_ptr;

  externalBounds.x = g.w;
  externalBounds.y = g.h;

  position(g);

  m_box.w = glm::clamp(measureChildren(Axis::X) + padding.get(Axis::X),
                      (float)bounds.min.x,
                      (float)maxWidth());

  m_box.h = glm::clamp(measureChildren(Axis::Y) + padding.get(Axis::Y),
                      (float)bounds.min.y,
                      (float)maxHeight());

  if (children.empty()) return;

  g.pad(padding);

  if (get(expand, direction)) {
    const Align dirAlign = align(direction);

    if (dirAlign != Align::START) {
      const float sizeDiff = offset(size(direction) - padding.get(direction),
                                    childrenSize(direction),
                                    dirAlign);

      g.translateClip(direction, sizeDiff);
    }
  }

  const Axis flipDir = flip(direction);
  const Align flipAlign = align(flipDir);

  const auto repaintChildBase = [&](unique_ptr<Widget> &w, Gctx &gctx) {
    if (get(w->expand, direction)) {
      const unsigned int prevSize = glm::max(0.0f, w->size(direction));
      w->repaint(gctx);
      set(w->externalBounds, direction, prevSize);
      w->updateSize(direction);
    } else {
      w->repaint(gctx);
    }
  };

  const auto repaintChild = [&](unique_ptr<Widget> &w) {
    repaintChildBase(w, g);
  };
  const auto repaintChildOffset = [&](unique_ptr<Widget> &w, float offset) {
    Gctx gCopy = g;
    gCopy.translateClip(flipDir, offset);
    repaintChildBase(w, gCopy);
  };

  bool isFirst = true;
  for (unique_ptr<Widget> &w : children) {
    if (isFirst) {
      isFirst = false;
    } else {
      g.translateClip(direction, spacing);
    }

    if (flipAlign == Align::START || get(w->expand, flipDir)) {
      repaintChild(w);
    } else {
      const float sizeDiff =
          size(flipDir) - padding.get(flipDir) - w->size(flipDir);

      if (sizeDiff <= 0.0f) {
        repaintChild(w);
      } else {
        repaintChildOffset(
            w, (flipAlign == Align::CENTER) ? (sizeDiff / 2.0f) : sizeDiff);
      }
    }

    g.translateClip(direction, w->size(direction));
  }
}

void Box::draw(glm::vec2 p) {
  if (p.x == x() && p.y == y()) {
    for (std::unique_ptr<Widget> &w : children) {
      w->draw();
    }
  } else {
    p.x += padding.left - x();
    p.y += padding.top - y();

    for (std::unique_ptr<Widget> &w : children) {
      w->draw({p.x + w->x(), p.y + w->y()});
    }
  }
}
} // namespace katzen::widgets
