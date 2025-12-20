#ifndef KATZE_BINS_PADDING_HPP
#define KATZE_BINS_PADDING_HPP

#include "../core/Edges.hpp"
#include "Capsule.hpp"

namespace katze {
struct Padding : Capsule {
  FEdges pad{};

  template <class T, typename = ifIsWidget<T>>
  Padding(float padding = 0.0f, std::shared_ptr<T> child = {})
    : Capsule(child), pad(padding) {}

  template <class T, typename = ifIsWidget<T>>
  Padding(float padding, T &&child) : Capsule(std::move(child)), pad(padding) {}

  template <class T, typename = ifIsWidget<T>>
  Padding(FEdges pad, std::shared_ptr<T> child = {})
    : Capsule(child), pad(pad) {}

  template <class T, typename = ifIsWidget<T>>
  Padding(FEdges pad, T &&child) : Capsule(std::move(child)), pad(pad) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
};
} // namespace katze

#endif // !KATZE_BINS_PADDING_HPP
