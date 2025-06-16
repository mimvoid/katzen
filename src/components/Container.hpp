#pragma once
#include <memory>
#include <vector>
#include "../widgets/Widget.hpp"

namespace katzen {
struct Container {
  std::vector<std::unique_ptr<Widget>> children{};

  template <typename T>
  void pushBack(T &&child) {
    children.push_back(std::make_unique<T>(std::move(child)));
  }

  template <typename T>
  T *pushBackGet(T &&child) {
    children.push_back(std::make_unique<T>(std::move(child)));
    return dynamic_cast<T *>(children.back().get());
  }

  template <typename T, typename... Args>
  void emplaceBack(Args &&...args) {
    children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  template <typename T, typename... Args>
  T *emplaceBackGet(Args &&...args) {
    children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T *>(children.back().get());
  }
};
} // namespace katzen
