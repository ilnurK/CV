#include "s21_snake.h"

namespace s21 {

Snake::Snake(Field &field) {
  dir_ = static_cast<dirs>(
      GetRandomNum(static_cast<int>(dirs::UP), static_cast<int>(dirs::RIGHT)));
  auto range_x_y = GetRandomRange();
  auto range_x{range_x_y.first}, range_y{range_x_y.second};
  size_t head_x{}, head_y{};
  head_x = static_cast<size_t>(GetRandomNum(static_cast<int>(range_x.first),
                                            static_cast<int>(range_x.second)));
  head_y = static_cast<size_t>(GetRandomNum(static_cast<int>(range_y.first),
                                            static_cast<int>(range_y.second)));
  InitData(head_x, head_y);
  PutOnField(field);
}

Snake::Snake(Field &field, dirs dir, xy_pair xy_snake) {
  dir_ = dir;
  size_t head_x{xy_snake.first}, head_y{xy_snake.second};
  InitData(head_x, head_y);
  PutOnField(field);
}

std::pair<xy_pair, xy_pair> Snake::GetRandomRange() {
  size_t x_min{}, x_max{}, y_min{}, y_max{}, min{2};
  if (dir_ == dirs::UP || dir_ == dirs::DOWN) {
    x_min = 0, x_max = Field::width - 1;
    if (dir_ == dirs::UP) {
      y_min = min, y_max = Field::height - size_;
    } else if (dir_ == dirs::DOWN) {
      y_min = size_ - 1, y_max = Field::height - 1 - min;
    }
  } else if (dir_ == dirs::LEFT || dir_ == dirs::RIGHT) {
    y_min = 0, y_max = Field::height - 1;
    if (dir_ == dirs::LEFT) {
      x_min = min, x_max = Field::width - size_;
    } else if (dir_ == dirs::RIGHT) {
      x_min = size_ - 1, x_max = Field::width - 1 - min;
    }
  }
  return {{x_min, x_max}, {y_min, y_max}};
}

void Snake::InitData(size_t x, size_t y) {
  size_t i{};
  if (dir_ == dirs::UP) {
    while (i < size_) {
      data_.push_back(std::make_pair(x, y + i++));
    }
  } else if (dir_ == dirs::DOWN) {
    while (i < size_) {
      data_.push_back(std::make_pair(x, y - i++));
    }
  } else if (dir_ == dirs::LEFT) {
    while (i < size_) {
      data_.push_back(std::make_pair(x + i++, y));
    }
  } else if (dir_ == dirs::RIGHT) {
    while (i < size_) {
      data_.push_back(std::make_pair(x - i++, y));
    }
  }
  head_ = data_.front();
}

void Snake::PutOnField(Field &field) {
  if (!data_.empty()) {
    for (auto it : data_) {
      field.At(it) = symbol_;
    }
    field.At(data_.front()) = head_symbol_;
    field.At(data_.back()) = tail_symbol_;
  }
}

void Snake::SetDirection(const dirs new_dir) {
  if (new_dir == dirs::UP) {
    if (dir_ == dirs::LEFT || dir_ == dirs::RIGHT) {
      dir_ = dirs::UP;
    }
  } else if (new_dir == dirs::DOWN) {
    if (dir_ == dirs::LEFT || dir_ == dirs::RIGHT) {
      dir_ = dirs::DOWN;
    }
  } else if (new_dir == dirs::LEFT) {
    if (dir_ == dirs::UP || dir_ == dirs::DOWN) {
      dir_ = dirs::LEFT;
    }
  } else if (new_dir == dirs::RIGHT) {
    if (dir_ == dirs::UP || dir_ == dirs::DOWN) {
      dir_ = dirs::RIGHT;
    }
  }
}

bool Snake::Move(Field &field) {
  bool flag_collided{false};
  if (dir_ == dirs::UP && head_.second > 0) {
    head_.second -= 1;
  } else if (dir_ == dirs::DOWN && head_.second < Field::height - 1) {
    head_.second += 1;
  } else if (dir_ == dirs::LEFT && head_.first > 0) {
    head_.first -= 1;
  } else if (dir_ == dirs::RIGHT && head_.first < Field::width - 1) {
    head_.first += 1;
  } else {
    flag_collided = true;
  }

  if (!flag_collided) {
    auto it = data_.begin(), ite = data_.end();
    if (std::find(it, ite, head_) == ite) {
      MoveData(field);
    } else {
      flag_collided = true;
    }
  }
  return flag_collided;
}

void Snake::MoveData(Field &field) {
  field.At(data_.front()) = symbol_;

  data_.push_front(head_);
  field.At(head_) = head_symbol_;

  old_tail_ = data_.back();
  field.At(old_tail_) = field.GetSymbol();
  data_.pop_back();

  field.At(data_.back()) = tail_symbol_;
}

void Snake::PlusSize(Field &field) {
  field.At(data_.back()) = symbol_;
  data_.push_back(old_tail_);
  field.At(old_tail_) = tail_symbol_;
  size_++;
};

}  // namespace s21
