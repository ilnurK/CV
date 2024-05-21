#ifndef S21_BRICK_GAME_SNAKE_CONTROLLER_H
#define S21_BRICK_GAME_SNAKE_CONTROLLER_H

#include "../../gui/desktop/brick_game/bg_src/s21_bg_keys.h"
#include "s21_snake_FSM.h"

namespace s21 {

class SnakeController {
 private:
  std::unique_ptr<SnakeFSM> snake_FSM_;

 public:
  size_t width{Field::width};
  size_t height{Field::height};

 public:
  SnakeController() : snake_FSM_(std::make_unique<SnakeFSM>()) {}
  SnakeController(bool, Dirs dir = Dirs::UP,
                  xy_pair xy_snake = {Field::width / 2, Field::height / 2},
                  xy_pair xy_apple = {Field::width / 2, 1})
      : snake_FSM_(std::make_unique<SnakeFSM>(dir, xy_snake, xy_apple)) {}
  ~SnakeController() {}

 public:
  using value = std::array<char, Field::width * Field::height>;
  GameStatus SetState(const SnakeStates& state,
                      const Dirs& dir = Dirs::NULL_DIR) {
    return snake_FSM_->SetState(state, dir);
  }
  void SetScore(const size_t score) { snake_FSM_->SetScore(score); }
  void SetHighScore(const size_t hscore) { snake_FSM_->SetHighScore(hscore); }
  void WriteScore() { snake_FSM_->WriteScore(); }

 public:
  value GetField() { return snake_FSM_->GetField()->GetData(); }
  std::deque<xy_pair> GetSnake() { return snake_FSM_->GetSnake()->GetData(); }
  size_t GetSnakeSize() { return snake_FSM_->GetSnake()->GetSize(); }
  xy_pair GetApple() { return snake_FSM_->GetApple()->GetCoords(); }
  size_t GetScore() { return snake_FSM_->GetScore(); }
  size_t GetHighScore() { return snake_FSM_->GetHighScore(); }
  size_t GetLevel() { return snake_FSM_->GetLevel(); }
  Dirs GetDirection() { return snake_FSM_->GetSnake()->GetDirection(); }
};

}  // namespace s21

#endif
