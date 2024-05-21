#include "s21_snake_FSM.h"

namespace s21 {

SnakeFSM::SnakeFSM()
    : field_(std::make_unique<Field>()),
      snake_(std::make_unique<Snake>(*field_)),
      apple_(std::make_unique<Apple>(*field_)) {
  InitHighScore();
}

SnakeFSM::SnakeFSM(Dirs dir, xy_pair xy_snake, xy_pair xy_apple)
    : field_(std::make_unique<Field>()),
      snake_(std::make_unique<Snake>(*field_, dir, xy_snake)),
      apple_(std::make_unique<Apple>(*field_, xy_apple)) {
  InitHighScore();
}

GameStatus SnakeFSM::SetState(const SnakeStates& state_in, const Dirs& dir_in) {
  GameStatus status{GameStatus::ON_AIR};

  size_t old_level = level_;
  SnakeStates state_out = StableFSM(state_in, dir_in);

  if (state_out == SnakeStates::WIN) {
    status = GameStatus::WIN;
  } else if (state_out == SnakeStates::GAME_OVER) {
    status = GameStatus::GAME_OVER;
  } else if (level_ - old_level) {
    status = GameStatus::LEVEL_UP;
  }
  return status;
}

SnakeStates SnakeFSM::StableFSM(const SnakeStates& state_in,
                                const Dirs& dir_in) {
  bool stable{false};
  SnakeFSM::value stable_state{stable, state_in};
  while (!stable) {
    stable_state = FSM(stable_state.second, dir_in);
    stable = stable_state.first;
  }
  return stable_state.second;
}

SnakeFSM::value SnakeFSM::FSM(const SnakeStates& state_in, const Dirs& dir_in) {
  bool stable{false};
  SnakeStates state_out{};
  if (state_in == SnakeStates::SHIFTING) {
    snake_->SetDirection(dir_in);
    state_out = SnakeStates::MOVING;
  } else if (state_in == SnakeStates::MOVING) {
    std::tie(stable, state_out) = Moving();
  } else if (state_in == SnakeStates::COLLIDED) {
    state_out = SnakeStates::GAME_OVER;
    stable = 1;
  } else if (state_in == SnakeStates::EATING) {
    apple_->Relocate(*field_);
    bool level_up_state{score_++ && score_ % level_coef_ == 0};
    level_ += (level_up_state && level_ < level_max_) ? 1 : 0;
    state_out = SnakeStates::GROWING;
  } else if (state_in == SnakeStates::GROWING) {
    snake_->PlusSize(*field_);
    if (score_ >= win_coef_) {
      state_out = SnakeStates::WIN;
    } else {
      state_out = SnakeStates::MOVING;
    }
    stable = 1;
  } else if (state_in == SnakeStates::START) {
    state_out = SnakeStates::MOVING;
  }
  return std::make_pair(stable, state_out);
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
  const char* home_dir = std::getenv("HOME");
  dir_ = std::string(home_dir) + std::string(score_dir_);
  if (!std::filesystem::exists(dir_)) {
    std::filesystem::create_directory(dir_);
  }
  std::filesystem::path file = dir_ + std::string(score_file_);
  if (std::filesystem::exists(file)) {
    std::ifstream ifile{file, std::ios::in};
    if (ifile.is_open()) {
      std::string line{};
      std::getline(ifile, line);
      if (!line.empty()) {
        highscore_ = std::stoul(line);
      }
      ifile.close();
    }
  }
}

void SnakeFSM::WriteScore() {
  size_t score{GetScore()};
  if (score > GetHighScore()) {
    highscore_ = score;
    std::filesystem::path file = dir_ + std::string(score_file_);
    std::ofstream ofile{file, std::ios::out};
    if (ofile.is_open()) {
      ofile << highscore_;
      ofile.close();
    }
  }
}

}  // namespace s21
