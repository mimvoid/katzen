#ifndef KATZE_CORE_STATE_HPP
#define KATZE_CORE_STATE_HPP

#include <cstdint>
#include "Rgba.hpp"

namespace katze {
enum class State : uint8_t { NORMAL, DISABLED, FOCUS, ACTIVE };

struct StateColors {
  Rgb border{};
  Rgb base{};
  Rgb text{};
};
} // namespace katze

#endif // KATZE_CORE_STATE_HPP
