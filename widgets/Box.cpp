#include "../widgets.hpp"
#include <algorithm>
#include <stdexcept>

Box::Box()
    : spacing(0), halign(Align::START), valign(Align::START),
      direction(Axis::X), children{} {}

Box::Box(int spacing, Axis direction, Align align, Align valign)
    : spacing(spacing), halign(align), valign(valign), direction(direction),
      children{} {}

Align Box::getAlign(Axis a) const {
  switch (a) {
    case Axis::X:
      return halign;
    case Axis::Y:
      return valign;
  }
}

float Box::measureChildren(Axis a) const {
  float size = 0.0f;

  if (children.empty())
    return size;

  if (a == direction) {
    const int childrenCount = children.size();
    size += spacing * (childrenCount - 1);

    std::vector<Widget *> expandedChildren;
    expandedChildren.reserve(childrenCount);

    for (auto &w : children) {
      if (w->expands(a)) {
        expandedChildren.push_back(w.get());
      } else {
        w->setExternalBound(getMaxSize(a) - getTotalPadding(a) - size, a);
        w->updateSize(a);
        size += w->getSize(a);
      }
    }

    if (!expandedChildren.empty()) {
      const float expandedSize =
          (getMaxSize(a) - getTotalPadding(a) - size) / expandedChildren.size();
      for (Widget *w : expandedChildren) {
        w->setExternalBound(expandedSize, a);
        w->updateSize(a);
        size += w->getSize(a);
      }
    }
  } else {
    float maxChildSize = 0.0f;
    for (auto &w : this->children) {
      w->setExternalBound(getMaxSize(a) - size, a);
      w->updateSize(a);
      maxChildSize = std::max(w->getSize(a), maxChildSize);
    }
    size += maxChildSize;
  }

  return size;
}

float Box::measureSize(Axis a) const {
  const float size = getTotalPadding(a) + measureChildren(a);
  return std::clamp(size, (float)getMinSize(a), (float)getMaxSize(a));
}

void Box::addChild(std::unique_ptr<Widget> &&w) {
  if (!w) {
    throw std::invalid_argument(
        "Cannot add null Widget pointer as a Box child");
  }

  children.push_back(std::move(w));
}

void Box::clearChildren() { children.clear(); }

void Box::repaint(Gctx g) {
  Widget::repaint(g);
  if (children.empty())
    return;

  pad(g);

  if (expands(direction)) {
    const Align dirAlign = getAlign(direction);
    if (dirAlign != Align::START) {
      float sizeDiff = getSize(direction) - getTotalPadding(direction) -
                       measureChildren(direction);

      if (dirAlign == Align::CENTER)
        sizeDiff /= 2.0f;

      TranslateClipGctx(g, direction, sizeDiff);
    }
  }

  const Axis flippedDir = flipAxis(direction);
  const Align flippedAlign = getAlign(flippedDir);

  const auto repaintChildBase = [&](std::unique_ptr<Widget> &w, Gctx &gctx) {
    if (w->expands(direction)) {
      const float prevSize = w->getSize(direction);
      w->repaint(gctx);
      w->setExternalBound(prevSize, direction);
      w->updateSize(direction);
    } else {
      w->repaint(gctx);
    }
  };

  const auto repaintChild = [&](std::unique_ptr<Widget> &w) {
    repaintChildBase(w, g);
  };
  const auto repaintChildOffset = [&](std::unique_ptr<Widget> &w,
                                      float offset) {
    Gctx gCopy = g;
    TranslateClipGctx(gCopy, flippedDir, offset);
    repaintChildBase(w, gCopy);
  };

  const int childrenCount = children.size();
  for (int i = 0; i < childrenCount; i++) {
    std::unique_ptr<Widget> &w = children.at(i);

    if (i != 0) {
      TranslateClipGctx(g, direction, spacing);
    }

    if (flippedAlign == Align::START || w->expands(flippedDir)) {
      repaintChild(w);
    } else {
      const float sizeDiff = getSize(flippedDir) - getTotalPadding(flippedDir) -
                             w->getSize(flippedDir);

      if (sizeDiff <= 0) {
        repaintChild(w);
      } else {
        repaintChildOffset(
            w, flippedAlign == Align::CENTER ? (sizeDiff / 2.0f) : sizeDiff);
      }
    }

    TranslateClipGctx(g, direction, w->getSize(direction));
  }
}

void Box::draw(Vector2 p) {
  if (p.x == getX() && p.y == getY()) {
    for (auto &w : children) {
      w->draw();
    }
  } else {
    p.x += padding.left - getX();
    p.y += padding.top - getY();

    for (auto &w : children) {
      w->draw({p.x + w->getX(), p.y + w->getY()});
    }
  }
}
