#pragma once
#include "../core/Dctx.hpp"
#include "Theme.hpp"

namespace katzen::theme {
Theme &getTheme();
Theme &setTheme(Theme newTheme);

StateColors &getStateColors(State state);
} // namespace katzen::theme
