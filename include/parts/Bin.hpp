#pragma once
#include <cassert>
#include <utility>

namespace katzen {
struct Widget;

template <class ChildT>
struct Bin {
  static_assert(std::is_base_of_v<Widget, ChildT>,
                "A child must be derived from a katzen Widget");

  ChildT child{};

  Bin() = default;
  Bin(ChildT &&child) : child(std::move(child)) {}

  template <typename... Args>
  Bin(Args &&...args) : child(std::forward<Args>(args)...) {}
};

template <class ChildT>
Bin(ChildT &&) -> Bin<ChildT>;

template <class ChildT>
struct BinBuilder {
  static_assert(std::is_base_of_v<Widget, ChildT>,
                "A child must be derived from a katzen Widget");

protected:
  ChildT m_child{};
};
} // namespace katzen
