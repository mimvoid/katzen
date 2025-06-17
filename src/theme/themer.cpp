#include "themer.hpp"
#include <optional>
#include <unordered_map>

namespace katzen::theme {
std::string_view currentThemeName;
std::unordered_map<std::string_view, Theme> themes{};

const Theme defaultTheme{
    2,
    0,
    1,
    {255, 245, 225, 255},
    {{242, 160, 164, 255}, {250, 223, 200, 255}, {39, 39, 42, 255}},
    {{217, 141, 150, 255}, {235, 192, 180, 255}, {57, 57, 60, 255}},
    {{248, 149, 155, 255}, {250, 214, 190, 255}, {39, 39, 42, 255}},
    {{54, 47, 64, 255}, {213, 132, 134, 255}, {252, 229, 233, 255}}};

void setDefaultTheme() {
  currentThemeName = "default";
  addTheme("default", defaultTheme);
}

void addTheme(std::string_view name, Theme theme) { themes[name] = theme; }
void setTheme(std::string_view name) {
  if (themes.find(name) != themes.end()) {
    currentThemeName = name;
  }
}

bool hasThemeName(std::string_view name) {
  return themes.find(name) != themes.end();
}

const Theme &getCurrentTheme() {
  const auto iter = themes.find(currentThemeName);
  return (iter == themes.end()) ? defaultTheme : iter->second;
}

std::optional<Theme> getTheme(std::string_view name) {
  const auto iter = themes.find(name);
  return (iter == themes.end()) ? std::nullopt
                                : std::optional<Theme>(iter->second);
}

Color getProperty(ColorProp property) {
  const Theme &t = getCurrentTheme();

  switch (property) {
  case ColorProp::BACKGROUND:      return t.backgroundColor;
  case ColorProp::NORMAL_BORDER:   return t.normal.border;
  case ColorProp::NORMAL_BASE:     return t.normal.base;
  case ColorProp::NORMAL_TEXT:     return t.normal.text;
  case ColorProp::DISABLED_BORDER: return t.disabled.border;
  case ColorProp::DISABLED_BASE:   return t.disabled.base;
  case ColorProp::DISABLED_TEXT:   return t.disabled.text;
  case ColorProp::FOCUS_BORDER:    return t.focus.border;
  case ColorProp::FOCUS_BASE:      return t.focus.base;
  case ColorProp::FOCUS_TEXT:      return t.focus.text;
  case ColorProp::ACTIVE_BORDER:   return t.active.border;
  case ColorProp::ACTIVE_BASE:     return t.active.base;
  case ColorProp::ACTIVE_TEXT:     return t.active.text;
  default:                         return BLANK;
  }
}

unsigned int getProperty(UIntProp property) {
  const Theme &t = getCurrentTheme();

  switch (property) {
  case UIntProp::BORDER_WIDTH:  return t.borderWidth;
  case UIntProp::BORDER_RADIUS: return t.borderRadius;
  case UIntProp::ICON_SIZE:     return t.iconSize;
  default:                      return 0;
  }
}

const StateColors &getStateColors(State state) {
  const Theme &t = getCurrentTheme();

  switch (state) {
  case State::DISABLED: return t.disabled;
  case State::FOCUS:    return t.focus;
  case State::ACTIVE:   return t.active;
  default:              return t.normal;
  }
}

void setProperty(ColorProp property, Color value) {
  const auto iter = themes.find(currentThemeName);
  if (iter == themes.end()) return;

  Theme &t = iter->second;

  switch (property) {
  case ColorProp::BACKGROUND:      t.backgroundColor = value; break;
  case ColorProp::NORMAL_BORDER:   t.normal.border = value; break;
  case ColorProp::NORMAL_BASE:     t.normal.base = value; break;
  case ColorProp::NORMAL_TEXT:     t.normal.text = value; break;
  case ColorProp::DISABLED_BORDER: t.disabled.border = value; break;
  case ColorProp::DISABLED_BASE:   t.disabled.base = value; break;
  case ColorProp::DISABLED_TEXT:   t.disabled.text = value; break;
  case ColorProp::FOCUS_BORDER:    t.focus.border = value; break;
  case ColorProp::FOCUS_BASE:      t.focus.base = value; break;
  case ColorProp::FOCUS_TEXT:      t.focus.text = value; break;
  case ColorProp::ACTIVE_BORDER:   t.active.border = value; break;
  case ColorProp::ACTIVE_BASE:     t.active.base = value; break;
  case ColorProp::ACTIVE_TEXT:     t.active.text = value; break;
  }
}

void setProperty(UIntProp property, unsigned int value) {
  const auto iter = themes.find(currentThemeName);
  if (iter == themes.end()) return;

  Theme &t = iter->second;

  switch (property) {
  case UIntProp::BORDER_WIDTH:  t.borderWidth = value; break;
  case UIntProp::BORDER_RADIUS: t.borderRadius = value; break;
  case UIntProp::ICON_SIZE:     t.iconSize = value; break;
  }
}
} // namespace katzen::theme
