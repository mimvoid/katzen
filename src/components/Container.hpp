#pragma once
#include <memory>
#include <vector>
#include "../widgets/Widget.hpp"

namespace katzen {
struct Container {
  std::vector<std::unique_ptr<Widget>> children{};

  template <typename T>
  void push(T &&child) {
    children.push_back(std::make_unique<T>(std::move(child)));
  }

  template <typename T, typename... Args>
  void emplace(Args &&...args) {
    children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }
};
} // namespace katzen
