#ifndef S21_BRICK_GAME_SNAKE_H
#define S21_BRICK_GAME_SNAKE_H

#include <algorithm>
#include <deque>
#include <iostream>

#include "s21_field.h"
#include "s21_support.h"

namespace s21 {

enum class Dirs { NULL_DIR, UP, DOWN, LEFT, RIGHT };

class Snake {
 private:
  xy_pair head_{};
  xy_pair old_tail_{};
  size_t size_{4};
  const char head_symbol_ = '0';
  const char symbol_ = 'O';
  const char tail_symbol_ = 'o';
  Dirs dir_{};
  std::deque<xy_pair> data_{};

 public:
  Snake(Field &field);
  Snake(Field &field, Dirs dir, xy_pair xy_snake);
  ~Snake() {}

 public:
  void SetDirection(const Dirs new_dir);

 public:
  xy_pair GetCoords() const { return head_; }
  Dirs GetDirection() const { return dir_; }
  size_t GetSize() const { return size_; }
  std::deque<xy_pair> &GetData() { return data_; }

 public:
  void PutOnField(Field &field);
  void PlusSize(Field &field);
  bool Move(Field &field);

 private:
  std::pair<xy_pair, xy_pair> GetRandomRange();
  void InitData(size_t x, size_t y);
  void MoveData(Field &field);
};

}  // namespace s21

#endif
