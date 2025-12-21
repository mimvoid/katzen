#ifndef KATZE_BINS_ICONLABEL_HPP
#define KATZE_BINS_ICONLABEL_HPP

#include "../widgets/Icon.hpp"
#include "../widgets/Label.hpp"
#include "Bin.hpp"

namespace katze {
struct IconLabel : Bin {
  Label label{};
  Icon icon{};

  FRect labelRect{};
  FRect iconRect{};

  int spacing{0};

  IconLabel() = default;

  IconLabel(Icon &&icon, Label &&label, int spacing = 0)
    : label(std::move(label)), icon(std::move(icon)), spacing(spacing) {}

  IconLabel(const IconBits &bits, const char *text = "", int spacing = 0)
    : label(text), icon(bits), spacing(spacing) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_BINS_ICONLABEL_HPP
