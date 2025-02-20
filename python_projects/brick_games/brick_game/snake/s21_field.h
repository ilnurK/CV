#ifndef S21_BRICK_GAME_FIELD_H
#define S21_BRICK_GAME_FIELD_H

#include <array>
#include <iostream>

namespace s21 {

/*
          field xy_pair
 0
  +------->
  |         x (width)
  |
  |
  v
    y (height)

*/

using xy_pair = std::pair<size_t, size_t>;

class Field {
 public:
  using reference = char &;
  using value = char;

 public:
  static const size_t width{10};
  static const size_t height{20};

 private:
  std::array<value, width * height> data_{};
  const value symbol_{' '};

 public:
  Field() { data_.fill(symbol_); }
  ~Field() {}

 public:
  reference At(const size_t x, const size_t y);
  value At(const size_t x, const size_t y) const;
  reference At(const xy_pair xy);
  value At(const xy_pair xy) const;

 public:
  value GetSymbol() const { return symbol_; }
  std::array<value, width * height> GetData() { return data_; }
};

}  // namespace s21

#endif
