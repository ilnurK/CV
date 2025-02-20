#ifndef S21_BRICK_GAME_SNAKE_GAME_H
#define S21_BRICK_GAME_SNAKE_GAME_H

#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>

#include "../s21_brick_games_highscores.h"
#include "s21_apple.h"

namespace s21 {

enum class SnakeStates {
  NULL_STATE = 0,
  START = 1,
  MOVING = 2,
  SHIFTING = 3,
  EATING = 4,
  GROWING = 5,
  COLLIDED = 6,
  GAME_OVER = 7,
  WIN = -1
};

class SnakeFSM {
 private:
  using dirs = S21Directions;
  SnakeStates state_{};
  std::unique_ptr<Field> field_;
  std::unique_ptr<Snake> snake_;
  std::unique_ptr<Apple> apple_;
  size_t score_{};
  size_t highscore_{};

  size_t win_coef_{200 - snake_->GetSize()};
  size_t level_{1};
  size_t level_coef_{5};
  size_t level_max_{10};

 public:
  SnakeFSM();
  SnakeFSM(dirs dir, xy_pair xy_snake, xy_pair xy_apple);

 private:
  using value = std::pair<bool, SnakeStates>;
  SnakeStates StableFSM(const SnakeStates &state_in, const dirs &dir_in);
  value FSM(const SnakeStates &state_in, dirs &dir_in);
  value Moving();
  void InitHighScore();

 public:
  SnakeStates SetState(const SnakeStates &state_in, const dirs &dir_in);
  void SetScore(const size_t score_in) { score_ = score_in; }
  void SetHighScore(const size_t highscore_in) { highscore_ = highscore_in; }
  void WriteHighScore();

 public:
  SnakeStates GetState() const { return state_; }
  Field *GetField() const { return field_.get(); }
  Snake *GetSnake() const { return snake_.get(); }
  Apple *GetApple() const { return apple_.get(); }
  size_t GetScore() const { return score_; }
  size_t GetHighScore() const { return highscore_; }
  size_t GetLevel() const { return level_; }
};

}  // namespace s21

#endif
