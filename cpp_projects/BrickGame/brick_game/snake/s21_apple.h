#ifndef S21_BRICK_GAME_APPLE_H
#define S21_BRICK_GAME_APPLE_H

#include <iostream>

#include "s21_snake.h"

namespace s21 {

class Apple {
 private:
  size_t x_{};
  size_t y_{};
  const char symbol_ = '@';

 public:
  Apple(Field &field);
  Apple(Field &field, xy_pair xy_apple);

 public:
  void SetCoords(const Field &field);

 public:
  xy_pair GetCoords() const { return std::make_pair(x_, y_); }

 public:
  void PutOnField(Field &field) { field.At(x_, y_) = symbol_; }
  void Relocate(Field &field);
};

}  // namespace s21

#endif