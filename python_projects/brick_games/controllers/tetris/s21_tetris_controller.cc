#include "s21_tetris_controller.h"

namespace s21 {

TetrisController::TetrisController() {
  ctrl_ = InitTetrisController(&error_);
  if (error_ == BAD_ALLOC) {
    throw std::runtime_error("Tetris controller bad initialization");
  }
}

S21TetrisStates TetrisController::SetState(const S21TetrisStates &state,
                                           const dirs &dir) {
  S21TetrisStates state_out = SetTetrisState(ctrl_, state, dir, &error_);
  return state_out;
}

TetrisController::field TetrisController::GetField() const {
  Controller::field fd{};
  int height{Controller::field_height}, width{Controller::field_width};
  for (int i{}; i < height; ++i) {
    for (int j{}; j < width; ++j) {
      fd[i * width + j] = *GetFieldAt(ctrl_, {j, i});
    }
  }
  return fd;
}

std::vector<std::pair<int, int>> TetrisController::GetAddInfo() {
  std::vector<std::pair<int, int>> vec{};
  vec.reserve(FIG_LEN);
  S21Figure *nf = ctrl_->fsm->next_figure;
  for (size_t i{}; i < FIG_LEN && nf; ++i) {
    vec.push_back({nf->data[i].y, nf->data[i].x});
  }
  return vec;
}

}  // namespace s21
