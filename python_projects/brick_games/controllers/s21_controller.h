#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include <array>
#include <cstddef>
#include <vector>

#include "../brick_game/s21_brick_games_directions.h"

namespace s21 {

using dirs = S21Directions;

template <typename T>
class Controller {
 public:
  static const size_t field_height{20};
  static const size_t field_width{10};

 public:
  virtual ~Controller() = default;

 public:
  virtual T SetState(const T &state, const dirs &dir = dirs::NULL_DIR) = 0;

 public:
  using field = std::array<char, field_height * field_width>;
  virtual T GetState() const = 0;
  virtual field GetField() const = 0;
  virtual size_t GetScore() const = 0;
  virtual size_t GetHighScore() const = 0;
  virtual size_t GetLevel() const = 0;
  size_t GetSpeed(size_t delay) { return delay * 0; }

 public:
  size_t GetAddInfoSize() const { return 0; }
  char GetAddInfoChar() const { return 0; }
  std::vector<std::pair<int, int>> GetAddInfo() {
    return std::vector<std::pair<int, int>>{};
  }
  virtual bool IsFilledCell(const char c) const = 0;

 public:
  virtual void SetHighScore(const size_t hscore) = 0;
  virtual void WriteHighScore() = 0;
};
}  // namespace s21

#endif
