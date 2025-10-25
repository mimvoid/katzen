#pragma once
#include <memory>
#include <vector>
#include "../widgets/Widget.hpp"

namespace katzen {
#define KATZEN_ASSERT_CONTAINER_WIDGET(type)     \
  static_assert(std::is_base_of_v<Widget, type>, \
                "A katzen Container can only have derivatives of Widget.");

struct Container {
  using value_type = std::unique_ptr<Widget>;

  template <class T>
  void push(T &&child) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    children.push_back(std::make_unique<T>(std::move(child)));
  }

  template <class T>
  T *pushGet(T &&child) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    children.push_back(std::make_unique<T>(std::move(child)));
    return dynamic_cast<T *>(children.back().get());
  }

  template <class T, typename... Args>
  void emplace(Args &&...args) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  template <class T, typename... Args>
  T *emplaceGet(Args &&...args) {
    KATZEN_ASSERT_CONTAINER_WIDGET(T);
    const std::unique_ptr<Widget> &ref =
        children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T *>(ref.get());
  }

protected:
  std::vector<value_type> children{};
};
} // namespace katzen
