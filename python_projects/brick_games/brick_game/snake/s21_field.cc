#include "s21_field.h"

namespace s21 {

Field::reference Field::At(const size_t x, const size_t y) {
  if (y > height - 1 || x > width - 1) {
    throw std::out_of_range("y must be < height and x must be < width\n");
  }
  return data_[y * width + x];
}

Field::value Field::At(const size_t x, const size_t y) const {
  if (y > height - 1 || x > width - 1) {
    throw std::out_of_range("y must be < height and x must be < width\n");
  }
  return data_[y * width + x];
}

Field::reference Field::At(const xy_pair xy) { return At(xy.first, xy.second); }

Field::value Field::At(const xy_pair xy) const {
  return At(xy.first, xy.second);
}

}  // namespace s21
