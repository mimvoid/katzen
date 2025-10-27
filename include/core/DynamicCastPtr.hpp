#pragma once
#include <memory>

namespace katzen {
/*
 * A wrapper around a weak_ptr for a base class, which can be locked and casted
 * to a shared_ptr of the derived class.
 */
template <typename From, typename To>
struct DynamicCastPtr {
  std::weak_ptr<From> ptr;

  constexpr std::shared_ptr<To> lock() const {
    return std::dynamic_pointer_cast<To>(ptr.lock());
  }
};
} // namespace katzen
