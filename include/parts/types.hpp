#pragma once
#include <type_traits>

namespace katzen {
struct Widget;

template <class T>
using ifIsWidget = std::enable_if_t<std::is_base_of_v<Widget, T>>;
} // namespace katzen
