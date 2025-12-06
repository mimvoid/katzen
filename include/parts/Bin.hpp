#pragma once
#include <cassert>
#include <utility>
#include "types.hpp"

namespace katzen {
template <class ChildT, typename = ifIsWidget<ChildT>>
struct Bin {
  ChildT child{};

  Bin() = default;
  Bin(ChildT &&child) : child(std::move(child)) {}

  template <typename... Args>
  Bin(Args &&...args) : child(std::forward<Args>(args)...) {}
};

template <class ChildT, typename DerivedT, typename = ifIsWidget<ChildT>>
struct BinBuilder {
  DerivedT &child(ChildT &&child) {
    m_child = std::move(child);
    return *static_cast<DerivedT *>(this);
  }

  template <typename... Args>
  DerivedT &emplaceChild(Args &&...args) {
    m_child = ChildT{std::forward<Args>(args)...};
    return *static_cast<DerivedT *>(this);
  }

protected:
  ChildT m_child{};
};
} // namespace katzen
