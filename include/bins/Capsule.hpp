#ifndef KATZE_BINS_CAPSULE_HPP
#define KATZE_BINS_CAPSULE_HPP

#include "Bin.hpp"

namespace katze {
/**
 * Bin that contains a single child widget.
 */
struct Capsule : Bin {
  std::shared_ptr<Widget> child{};
  FRect childRect{};

  Capsule(std::shared_ptr<Widget> child = {}) : child(child) {}

  template <class T>
  Capsule(T &&child) : child(std::make_shared<T>(std::move(child))) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_BINS_CAPSULE_HPP
