#pragma once
#include <memory>
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

#define KATZEN_ASSERT_CONTAINER_WIDGET(type)     \
  static_assert(std::is_base_of_v<Widget, type>, \
                "A katzen Container can only have derivatives of Widget.");

template <class T>
void pushWidget(std::vector<std::shared_ptr<Widget>> &children, T &&child) {
  KATZEN_ASSERT_CONTAINER_WIDGET(T);
  children.push_back(std::make_shared<T>(std::move(child)));
}

template <class T, typename... Args>
void emplaceWidget(std::vector<std::shared_ptr<Widget>> &children, Args &&...args) {
  KATZEN_ASSERT_CONTAINER_WIDGET(T);
  children.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
}

struct Container {
  using value_type = std::shared_ptr<Widget>;

  template <class T>
  void push(T &&child) {
    pushWidget<T>(children, std::move(child));
  }

  template <class T>
  WidgetPtr<T> pushGet(T &&child) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    children.push_back(std::make_shared<T>(std::move(child)));
    return {std::weak_ptr(children.back())};
  }

  template <class T, typename... Args>
  void emplace(Args &&...args) {
    emplaceWidget<T>(children, std::forward<Args>(args)...);
  }

  template <class T, typename... Args>
  WidgetPtr<T> emplaceGet(Args &&...args) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    const value_type &ref =
        children.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    return {std::weak_ptr(ref)};
  }

protected:
  std::vector<value_type> children{};
};
} // namespace katzen
