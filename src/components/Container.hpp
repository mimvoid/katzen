#pragma once
#include <memory>
#include <vector>
#include "../widgets/Widget.hpp"

namespace katzen {
#define STATIC_ASSERT_WIDGET(type)               \
  static_assert(std::is_base_of_v<Widget, type>, \
                "A katzen Container can only have derivatives of Widget.");

struct Container {
  using value_type = std::unique_ptr<Widget>;
  std::vector<value_type> children{};

  template <class T>
  void pushBack(T &&child) {
    STATIC_ASSERT_WIDGET(T);
    children.push_back(std::make_unique<T>(std::move(child)));
  }

  template <class T>
  T *pushBackGet(T &&child) {
    STATIC_ASSERT_WIDGET(T);
    children.push_back(std::make_unique<T>(std::move(child)));
    return dynamic_cast<T *>(children.back().get());
  }

  template <class T, typename... Args>
  void emplaceBack(Args &&...args) {
    STATIC_ASSERT_WIDGET(T);
    children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  template <class T, typename... Args>
  T *emplaceBackGet(Args &&...args) {
    STATIC_ASSERT_WIDGET(T);
    const std::unique_ptr<Widget> &ref =
        children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T *>(ref.get());
  }
};
} // namespace katzen
