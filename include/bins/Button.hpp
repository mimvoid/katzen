#ifndef KATZE_BINS_CLICKABLE_HPP
#define KATZE_BINS_CLICKABLE_HPP

#include "../Reactive.hpp"
#include "Capsule.hpp"

namespace katze {
struct Clickable : Capsule, Reactive {
  uint32_t onClick{0};

  Clickable() = default;

  template <class T, typename = ifIsWidget<T>>
  Clickable(std::shared_ptr<T> child) : Capsule(child) {}

  template <class T, typename = ifIsWidget<T>>
  Clickable(std::shared_ptr<T> child, uint32_t onClick)
    : Capsule(child), onClick(onClick) {
    enabled = true;
  }

  template <class T, typename = ifIsWidget<T>>
  Clickable(T &&child) : Capsule(std::move(child)) {}

  template <class T, typename = ifIsWidget<T>>
  Clickable(T &&child, uint32_t onClick)
    : Capsule(std::move(child)), onClick(onClick) {
    enabled = true;
  }

  void view(Dctx &d, FRect rect) override;
};

struct Button : Clickable {
  int padding{8};

  Button() = default;

  template <class T, typename = ifIsWidget<T>>
  Button(std::shared_ptr<T> child) : Clickable(child) {}

  template <class T, typename = ifIsWidget<T>>
  Button(std::shared_ptr<T> child, uint32_t onClick)
    : Clickable(child, onClick) {}

  template <class T, typename = ifIsWidget<T>>
  Button(T &&child) : Clickable(std::move(child)) {}

  template <class T, typename = ifIsWidget<T>>
  Button(T &&child, uint32_t onClick) : Clickable(std::move(child), onClick) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_BINS_CLICKABLE_HPP
