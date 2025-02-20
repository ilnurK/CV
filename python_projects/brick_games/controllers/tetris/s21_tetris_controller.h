#ifndef S21_BRICK_GAME_TETRIS_CONTROLLER_H
#define S21_BRICK_GAME_TETRIS_CONTROLLER_H

#include <iostream>
#include <memory>
#include <stdexcept>

#include "../s21_controller.h"
#include "s21_tetris_controller_c.h"
namespace s21 {

class TetrisController : public Controller<S21TetrisStates> {
 private:
  S21TetrisError error_{};
  S21TetrisCController *ctrl_{};

 public:
  TetrisController();
  ~TetrisController() { DeleteController(ctrl_); }
  TetrisController(const TetrisController &) = delete;
  TetrisController &operator=(const TetrisController &) = delete;
  TetrisController(TetrisController &&other) {
    if (this != &other) {
      this->ctrl_ = other.ctrl_;
      other.ctrl_ = nullptr;
    }
  }
  TetrisController &operator=(TetrisController &&other) {
    if (this != &other) {
      this->ctrl_ = other.ctrl_;
      other.ctrl_ = nullptr;
    }
    return *this;
  }

 public:
  S21TetrisStates SetState(const S21TetrisStates &state,
                           const dirs &dir) override;

 public:
  S21TetrisStates GetState() const override { return ctrl_->fsm->state; }
  field GetField() const override;
  size_t GetScore() const override { return ctrl_->fsm->score; }
  size_t GetHighScore() const override { return ctrl_->fsm->highscore; }
  size_t GetLevel() const override { return ctrl_->fsm->level; }

  void SetHighScore(const size_t hscore) { ctrl_->fsm->highscore = hscore; }
  void WriteHighScore() override { WriteTetrisHighScore(ctrl_, &error_); }
  bool IsFilledCell(const char c) const override {
    return c == ctrl_->field_symb_fill || c == ctrl_->field_symb_fig;
  }

 public:
  size_t GetAddInfoSize() const { return ctrl_->fig_len; }
  char GetAddInfoChar() const { return ctrl_->fig_symb; }
  std::vector<std::pair<int, int>> GetAddInfo();
};
}  // namespace s21
#endif