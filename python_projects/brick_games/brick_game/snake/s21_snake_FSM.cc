#include "s21_snake_FSM.h"

namespace s21 {

SnakeFSM::SnakeFSM()
    : field_(std::make_unique<Field>()),
      snake_(std::make_unique<Snake>(*field_)),
      apple_(std::make_unique<Apple>(*field_)) {
  InitHighScore();
}

SnakeFSM::SnakeFSM(dirs dir, xy_pair xy_snake, xy_pair xy_apple)
    : field_(std::make_unique<Field>()),
      snake_(std::make_unique<Snake>(*field_, dir, xy_snake)),
      apple_(std::make_unique<Apple>(*field_, xy_apple)) {
  InitHighScore();
}

SnakeStates SnakeFSM::SetState(const SnakeStates &state_in,
                               const dirs &dir_in) {
  SnakeStates state = StableFSM(state_in, dir_in);
  return state;
}

SnakeStates SnakeFSM::StableFSM(const SnakeStates &state_in,
                                const dirs &dir_in) {
  bool stable{false};
  SnakeFSM::value stable_state{stable, state_in};
  dirs dir = dir_in;
  while (!stable) {
    stable_state = FSM(stable_state.second, dir);
    stable = stable_state.first;
  }
  return stable_state.second;
}

SnakeFSM::value SnakeFSM::FSM(const SnakeStates &state_in, dirs &dir_in) {
  bool stable{false};
  if (dir_in && state_ != SnakeStates::SHIFTING) {
    state_ = SnakeStates::SHIFTING;
  } else if (state_in == SnakeStates::SHIFTING) {
    snake_->SetDirection(dir_in);
    state_ = SnakeStates::MOVING;
    dir_in = NULL_DIR;
  } else if (state_in == SnakeStates::MOVING) {
    std::tie(stable, state_) = Moving();
  } else if (state_in == SnakeStates::COLLIDED) {
    state_ = SnakeStates::GAME_OVER;
    if (score_ > highscore_) {
      highscore_ = score_;
    }
    stable = 1;
  } else if (state_in == SnakeStates::EATING) {
    apple_->Relocate(*field_);
    state_ = SnakeStates::GROWING;
  } else if (state_in == SnakeStates::GROWING) {
    state_ = SnakeStates::MOVING;
    snake_->PlusSize(*field_);
    bool level_up_state{score_++ && score_ % level_coef_ == 0};
    level_ += (level_up_state && level_ < level_max_) ? 1 : 0;
    if (score_ >= win_coef_) {
      state_ = SnakeStates::WIN;
    }
    stable = 1;
  } else if (state_in == SnakeStates::START) {
    state_ = SnakeStates::MOVING;
  }
  return std::make_pair(stable, state_);
}

SnakeFSM::value SnakeFSM::Moving() {
  SnakeStates state_out{};
  bool stable{false};

  bool flag_collided = snake_->Move(*field_);

  if (flag_collided) {
    state_out = SnakeStates::COLLIDED;
  } else if (snake_->GetCoords() == apple_->GetCoords()) {
    state_out = SnakeStates::EATING;
  } else {
    state_out = SnakeStates::MOVING;
    stable = true;
  }
  return std::make_pair(stable, state_out);
}

void SnakeFSM::InitHighScore() {
  bool is_creating_error{};
  highscore_ = S21InitHighScore(snake_log_file_name, &is_creating_error);
  if (is_creating_error) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
}

void SnakeFSM::WriteHighScore() {
  bool is_writing_error = S21WriteHighScore(snake_log_file_name, highscore_);
  if (is_writing_error) {
    throw std::runtime_error(__PRETTY_FUNCTION__);
  }
}

}  // namespace s21
