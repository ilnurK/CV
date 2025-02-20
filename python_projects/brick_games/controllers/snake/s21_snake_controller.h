#ifndef S21_BRICK_GAME_SNAKE_CONTROLLER_H
#define S21_BRICK_GAME_SNAKE_CONTROLLER_H

#include "../../brick_game/snake/s21_snake_FSM.h"
#include "../s21_controller.h"

namespace s21 {

class SnakeController : public Controller<SnakeStates> {
 private:
  std::unique_ptr<SnakeFSM> snake_FSM_;

 public:
  size_t width{Field::width};
  size_t height{Field::height};

 public:
  SnakeController() : snake_FSM_(std::make_unique<SnakeFSM>()) {}

  SnakeController(bool, dirs dir = dirs::UP,
                  xy_pair xy_snake = {Field::width / 2, Field::height / 2},
                  xy_pair xy_apple = {Field::width / 2, 1})
      : snake_FSM_(std::make_unique<SnakeFSM>(dir, xy_snake, xy_apple)) {
  }  // for tests

 public:
  SnakeStates SetState(const SnakeStates &state, const dirs &dir) override {
    return snake_FSM_->SetState(state, dir);
  }

 public:
  Controller::field GetField() const override {
    return snake_FSM_->GetField()->GetData();
  }

  size_t GetScore() const override { return snake_FSM_->GetScore(); }
  size_t GetHighScore() const override { return snake_FSM_->GetHighScore(); }
  size_t GetLevel() const override { return snake_FSM_->GetLevel(); }
  SnakeStates GetState() const override { return snake_FSM_->GetState(); }

 public:
  void SetHighScore(const size_t hscore) override {
    snake_FSM_->SetHighScore(hscore);
  }
  void SetScore(const size_t score) { snake_FSM_->SetScore(score); }
  void WriteHighScore() override { snake_FSM_->WriteHighScore(); }
  bool IsFilledCell(const char c) const override {
    return (c == snake_FSM_->GetApple()->GetSymbol() ||
            snake_FSM_->GetSnake()->IsFilledCell(c));
  }

 public:
  std::deque<xy_pair> GetSnake() { return snake_FSM_->GetSnake()->GetData(); }
  size_t GetSnakeSize() { return snake_FSM_->GetSnake()->GetSize(); }
  xy_pair GetApple() { return snake_FSM_->GetApple()->GetCoords(); }
  dirs GetDirection() { return snake_FSM_->GetSnake()->GetDirection(); }
};

extern "C" {
SnakeFSM *GetSnakeFSM();
SnakeController *GetSnakeController();
void DeleteSnakeController(SnakeController *ctrl);
SnakeStates SetSnakeState(SnakeController *ctrl, int state, int dir);
char GetSnakeFieldAt(SnakeController *ctrl, int x, int y);
size_t GetSnakeScore(SnakeController *ctrl);
size_t GetSnakeHighScore(SnakeController *ctrl);
size_t GetSnakeLevel(SnakeController *ctrl);
size_t GetSnakeFieldHeight(SnakeController *ctrl);
size_t GetSnakeFieldWidth(SnakeController *ctrl);
}

}  // namespace s21

#endif
