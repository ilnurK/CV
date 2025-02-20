#ifndef S21_BRICK_GAME_CLI_VIEW_H
#define S21_BRICK_GAME_CLI_VIEW_H

#include <ncurses.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <map>
#include <typeinfo>

#include "../../brick_game/s21_brick_games_directions.h"
#include "../../controllers/race/s21_race_controller.h"
#include "../../controllers/snake/s21_snake_controller.h"
#include "../../controllers/tetris/s21_tetris_controller.h"
#include "s21_brick_games_keys.h"

namespace s21 {

class CliViewBase {
 public:
  virtual void Play(WINDOW *win_in) = 0;
  virtual ~CliViewBase() = default;
};

template <typename C, typename S>
class CliView : public CliViewBase {
 private:
  WINDOW *win_;
  C ctrl_{};
  S state_{};

 private:
  size_t score_{};
  size_t highscore_{};
  size_t level_{};
  size_t delay_{};

 private:
  int key_in_{KEY_NULL_};
  size_t std_speed_{600};
  bool is_pause_{};

 private:
  size_t extra_info_size_{};
  char extra_info_char_{};
  std::vector<std::pair<int, int>> extra_info_{};

 private:
  const char field_corner_ = '+';
  const char field_horizontal_ = '-';
  const char field_vertical_ = '|';

 private:
  const int y_side_ = 6;
  const int x_side_ = 13;

 public:
  CliView() = default;
  CliView &operator=(const CliView &other) = default;
  CliView &operator=(CliView &&other) = default;
  ~CliView() {
    if (score_ > highscore_ && (state_ != S::GAME_OVER && state_ != S::WIN)) {
      ctrl_.SetHighScore(score_);
      ctrl_.WriteHighScore();
    }
  }

 public:
  void Play(WINDOW *win_in) override;

 private:
  void InitExtraInfo();
  void PlayFSM();
  bool IsEndState() { return state_ == S::GAME_OVER || state_ == S::WIN; }
  bool IsNotEndKey(int key) { return key != KEY_QUIT_ && key != KEY_QUIT_L_; }
  void DrawField();
  void DrawHorizontalFrame(const size_t width);
  void DrawSideMenu();

  using dirs = S21Directions;
  dirs KeysConvert();

 private:
  std::map<int, dirs> keys_to_dir_ = {{KEY_UP_, UP},
                                      {KEY_DOWN_, DOWN},
                                      {KEY_LEFT_, LEFT},
                                      {KEY_RIGHT_, RIGHT},
                                      {KEY_ACTION_, ACTION}};
};

}  // namespace s21

#include "s21_cli_view.tpp"
#endif