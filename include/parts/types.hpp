#pragma once
#include <type_traits>
#include "../core/DynamicCastPtr.hpp"

namespace katzen {
struct Widget;

/**
 * Katzen's containers store their children with shared_ptr, and return stored
 * children with weak_ptr.
 *
 * If a child is added with methods like pushGet and emplaceGet, then the
 * derived class is known, so this helps to couple the derived class with the
 * weak_ptr.
 */
template <typename To>
using WidgetPtr = DynamicCastPtr<Widget, To>;

template <class T>
using ifIsWidget = std::enable_if_t<std::is_base_of_v<Widget, T>>;
} // namespace katzen
