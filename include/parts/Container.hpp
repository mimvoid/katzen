#pragma once
#include <memory>
#include <type_traits>
#include <vector>
#include "../core/DynamicCastPtr.hpp"

namespace katzen {
struct Widget;

/**
 * Container widgets in katzen store their children with shared_ptr, and return
 * stored children with weak_ptr.
 *
 * If a child is added with methods like pushGet and emplaceGet, then the
 * derived class is known, so this helps to couple the derived class with the
 * weak_ptr.
 */
template <typename To>
using WidgetPtr = DynamicCastPtr<Widget, To>;

template <class T>
constexpr void checkIsWidget() {
  static_assert(std::is_base_of_v<Widget, T>,
                "A katzen Container can only have derivatives of Widget.");
}

struct OpaqueContainer {
  using value_type = std::shared_ptr<Widget>;
  using size_type = std::vector<value_type>::size_type;

  template <class T>
  void push(T &&child) {
    checkIsWidget<T>();
    m_children.push_back(std::make_shared<T>(std::move(child)));
  }

  template <class T, typename... Args>
  void emplace(Args &&...args) {
    checkIsWidget<T>();
    m_children.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
  }

  template <class T, typename... Args>
  void emplaceAt(size_type pos, Args &&...args) {
    checkIsWidget<T>();
    m_children.emplace(m_children.cbegin() + pos,
                       std::make_shared<T>(std::forward<Args>(args)...));
  }

  template <class T>
  void insert(size_type pos, T &&child) {
    checkIsWidget<T>();
    m_children.insert(m_children.cbegin() + pos,
                      std::make_shared<T>(std::move(child)));
  }

  // Wrapper around std::vector::reserve for the underlying children vector.
  void reserve(size_type newCap) { m_children.reserve(newCap); }

protected:
  std::vector<value_type> m_children{};
};

struct Container : OpaqueContainer {
  using OpaqueContainer::value_type;
  using OpaqueContainer::size_type;

  template <class T>
  WidgetPtr<T> pushGet(T &&child) {
    checkIsWidget<T>();
    m_children.push_back(std::make_shared<T>(std::move(child)));
    return {std::weak_ptr(m_children.back())};
  }

  template <class T, typename... Args>
  WidgetPtr<T> emplaceGet(Args &&...args) {
    checkIsWidget<T>();
    const value_type &ref = m_children.emplace_back(
        std::make_shared<T>(std::forward<Args>(args)...));
    return {std::weak_ptr(ref)};
  }
};

template <typename DerivedT>
struct ContainerBuilder : protected OpaqueContainer {
  template <class T>
  DerivedT &push(T &&child) {
    OpaqueContainer::push<T>(std::move(child));
    return *static_cast<DerivedT *>(this);
  }

  template <class T, typename... Args>
  DerivedT &emplace(Args &&...args) {
    OpaqueContainer::emplace<T>(std::forward<Args>(args)...);
    return *static_cast<DerivedT *>(this);
  }

  template <class T, typename... Args>
  DerivedT &emplaceAt(size_type pos, Args &&...args) {
    OpaqueContainer::emplaceAt<T>(pos, std::forward<Args>(args)...);
    return *static_cast<DerivedT *>(this);
  }

  template <class T>
  DerivedT &insert(size_type pos, T &&child) {
    OpaqueContainer::insert(pos, std::move(child));
    return *static_cast<DerivedT *>(this);
  }

  DerivedT &reserve(size_type newCap) {
    OpaqueContainer::reserve(newCap);
    return *static_cast<DerivedT *>(this);
  }
};
} // namespace katzen
