#ifndef KATZE_WIDGETS_CHECKBOX_HPP
#define KATZE_WIDGETS_CHECKBOX_HPP

#include "../Reactive.hpp"
#include "Widget.hpp"

namespace katze {
struct Checkbox : Widget, Reactive {
  bool checked{false};
  uint32_t onCheck{0};

  Checkbox(bool checked = false) : checked(checked) {}
  Checkbox(bool checked, uint32_t onCheck)
    : Reactive(true), checked(checked), onCheck(onCheck) {}

  void resize(Gctx g, FRect &rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_CHECKBOX_HPP
