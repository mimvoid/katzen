#include "bins/Bin.hpp"

namespace katze {
Bin *dynCastBin(Widget *ptr) { return dynamic_cast<Bin *>(ptr); }

std::shared_ptr<Bin> dynCastBin(std::shared_ptr<Widget> ptr) {
  return std::dynamic_pointer_cast<Bin, Widget>(ptr);
}
} // namespace katze
