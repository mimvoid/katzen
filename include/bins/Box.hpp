#ifndef KATZE_BINS_BOX_HPP
#define KATZE_BINS_BOX_HPP

#include <vector>
#include "../core/Align.hpp"
#include "Bin.hpp"

namespace katze {
struct Box : Bin {
  using value_type = std::shared_ptr<Widget>;

  int spacing;
  Axis direction;
  AlignVec2 align;

  Box(
    int spacing = 0,
    Axis direction = Axis::X,
    Align halign = Align::START,
    Align valign = Align::START
  )
    : spacing(spacing), direction(direction), align(halign, valign) {}

  constexpr const std::vector<value_type> &children() const {
    return m_children;
  }

  template <class T, typename = ifIsWidget<T>>
  void push(std::shared_ptr<T> child, bool expanded = false) {
    m_children.push_back(child);
    m_childRects.emplace_back();
    m_expanded.push_back(expanded);
  }

  template <class T, typename = ifIsWidget<T>>
  void push(T &&child, bool expanded = false) {
    push(std::make_shared<T>(std::move(child)), expanded);
  }

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;

protected:
  std::vector<value_type> m_children{};
  std::vector<FRect> m_childRects{};
  std::vector<bool> m_expanded{};

  float m_expandedSize{0.0f};

  FVec2 resizeChildren(Gctx g);
  float measureChildren(float bound) const;
};
} // namespace katze

#endif // !KATZE_BINS_BOX_HPP
