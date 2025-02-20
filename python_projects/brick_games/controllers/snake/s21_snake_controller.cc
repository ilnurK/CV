#include "s21_snake_controller.h"

namespace s21 {
extern "C" {
#include <iostream>

SnakeFSM *GetSnakeFSM() { return new SnakeFSM(); }

SnakeController *GetSnakeController() {
  try {
    SnakeController *ctrl = new SnakeController();
    return ctrl;
  } catch (const std::exception &e) {
    std::cerr << "SnakeController init error: " << e.what() << std::endl;
    return nullptr;
  }
}

void DeleteSnakeController(SnakeController *ctrl) { delete ctrl; }

SnakeStates SetSnakeState(SnakeController *ctrl, int state, int dir) {
  return ctrl->SetState(static_cast<SnakeStates>(state),
                        static_cast<dirs>(dir));
}

char GetSnakeFieldAt(SnakeController *ctrl, int x, int y) {
  SnakeController::field f = ctrl->GetField();
  return f[y * ctrl->width + x];
}

size_t GetSnakeScore(SnakeController *ctrl) { return ctrl->GetScore(); }
size_t GetSnakeHighScore(SnakeController *ctrl) { return ctrl->GetHighScore(); }
size_t GetSnakeLevel(SnakeController *ctrl) { return ctrl->GetLevel(); }

size_t GetSnakeFieldHeight(SnakeController *ctrl) { return ctrl->height; }
size_t GetSnakeFieldWidth(SnakeController *ctrl) { return ctrl->width; }
}
}  // namespace s21
