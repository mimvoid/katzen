#pragma once
#include <optional>
#include <string_view>
#include "../core/Dctx.hpp"
#include "Theme.hpp"

namespace katzen::theme {
enum class ColorProp {
  BACKGROUND,
  NORMAL_BORDER,
  NORMAL_BASE,
  NORMAL_TEXT,
  DISABLED_BORDER,
  DISABLED_BASE,
  DISABLED_TEXT,
  FOCUS_BORDER,
  FOCUS_BASE,
  FOCUS_TEXT,
  ACTIVE_BORDER,
  ACTIVE_BASE,
  ACTIVE_TEXT,
};

enum class UIntProp {
  BORDER_WIDTH,
  BORDER_RADIUS,
  ICON_SIZE,
};

// Initializes with the default theme
void setDefaultTheme();

void addTheme(std::string_view name, Theme theme);
void setTheme(std::string_view name);

bool hasThemeName(std::string_view name);
const Theme &getCurrentTheme();
std::optional<Theme> getTheme(std::string_view name);

Color getProperty(ColorProp property);
unsigned int getProperty(UIntProp property);

const StateColors &getStateColors(State state);

void setProperty(ColorProp property, Color value);
void setProperty(UIntProp property, unsigned int value);
} // namespace katzen::theme
