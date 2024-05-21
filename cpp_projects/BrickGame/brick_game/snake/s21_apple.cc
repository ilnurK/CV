#include "s21_apple.h"

#include <vector>

namespace s21 {

Apple::Apple(Field &field) {
  SetCoords(field);
  PutOnField(field);
}

Apple::Apple(Field &field, xy_pair xy_apple) {
  std::tie(x_, y_) = xy_apple;
  PutOnField(field);
}

void Apple::SetCoords(const Field &field) {
  std::vector<xy_pair> free_slots{};
  char c = field.GetSymbol();
  for (size_t y{}; y < Field::height; y++) {
    for (size_t x{}; x < Field::width; x++) {
      if (field.At(x, y) == c) {
        free_slots.push_back({x, y});
      }
    }
  }
  int rnd_pos = GetRandomNum(0, static_cast<int>(free_slots.size() - 1));
  std::tie(x_, y_) = free_slots[static_cast<size_t>(rnd_pos)];
}

void Apple::Relocate(Field &field) {
  SetCoords(field);
  PutOnField(field);
}

}  // namespace s21