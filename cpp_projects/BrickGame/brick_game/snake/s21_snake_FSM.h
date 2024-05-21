#ifndef S21_BRICK_GAME_SNAKE_GAME_H
#define S21_BRICK_GAME_SNAKE_GAME_H

#include <filesystem>
#include <fstream>
#include <memory>

#include "s21_apple.h"

namespace s21 {

enum class SnakeStates {
  START = 1,
  MOVING = 2,
  SHIFTING = 3,
  EATING = 4,
  GROWING = 5,
  COLLIDED = 6,
  GAME_OVER = 7,
  WIN = 8
};

enum class GameStatus { ON_AIR, LEVEL_UP, WIN, GAME_OVER };

class SnakeFSM {
 private:
  std::unique_ptr<Field> field_;
  std::unique_ptr<Snake> snake_;
  std::unique_ptr<Apple> apple_;
  size_t score_{};
  size_t highscore_{};
  std::string dir_;
  const char *score_dir_ = "/brick_game_logs";
  const char *score_file_ = "/snake_score.log";

  size_t win_coef_{200 - snake_->GetSize()};
  size_t level_{1};
  size_t level_coef_{5};
  size_t level_max_{10};

 public:
  using value = std::pair<bool, SnakeStates>;
  SnakeFSM();
  SnakeFSM(Dirs dir, xy_pair xy_snake, xy_pair xy_apple);

 public:
  GameStatus SetState(const SnakeStates &status_in, const Dirs &dir_in);
  void SetScore(const size_t score_in) { score_ = score_in; }
  void SetHighScore(const size_t highscore_in) { highscore_ = highscore_in; }
  void WriteScore();

 public:
  Field *GetField() const { return field_.get(); }
  Snake *GetSnake() const { return snake_.get(); }
  Apple *GetApple() const { return apple_.get(); }
  size_t GetScore() const { return score_; }
  size_t GetHighScore() const { return highscore_; }
  size_t GetLevel() const { return level_; }

 private:
  SnakeStates StableFSM(const SnakeStates &status_in, const Dirs &dir_in);
  value FSM(const SnakeStates &status_in, const Dirs &dir_in);
  value Moving();
  void InitHighScore();
};

}  // namespace s21

#endif
