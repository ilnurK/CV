#ifndef S21_BRICK_GAME_CLI_VIEW_H
#define S21_BRICK_GAME_CLI_VIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <algorithm>
#include <fstream>
#include <map>

#include "../../../brick_game/s21_brick_games_directions.h"
#include "../../../controllers/race/s21_race_controller.h"
#include "../../../controllers/snake/s21_snake_controller.h"
#include "../../../controllers/tetris/s21_tetris_controller.h"
#include "s21_bg_keys.h"

namespace s21 {

class MainWindow;

class DesktopViewBase {
 public:
  virtual ~DesktopViewBase() = default;
  virtual void Play() = 0;
  virtual bool IsPause() const = 0;
};

template <typename C, typename S>
class DesktopView : public DesktopViewBase {
 private:
  MainWindow *win_;
  QScopedPointer<QGraphicsScene> scene_{};
  C ctrl_{};
  S state_{};

 private:
  size_t score_{};
  size_t highscore_{};
  size_t level_{};
  size_t delay_{};
  size_t speed_{};

 private:
  Keys key_in_{Keys::KEY_NULL};
  size_t std_speed_{600};
  bool is_pause_{};

  size_t margin_{2};

 private:
  QScopedPointer<QGraphicsTextItem> end_text_;

 private:
  QScopedPointer<QGraphicsScene> extra_scene_{};
  size_t extra_info_size_{};
  char extra_info_char_{};
  std::vector<std::pair<int, int>> extra_info_{};

 public:
  DesktopView(MainWindow *win_in);
  DesktopView &operator=(const DesktopView &other) = default;
  DesktopView &operator=(DesktopView &&other) = default;
  ~DesktopView() {
    if (score_ > highscore_ && win_->GetPlayingStatus()) {
      ctrl_.SetHighScore(score_);
      ctrl_.WriteHighScore();
    }
  };

 public:
  void Play() override;
  bool IsPause() const override { return is_pause_; }

 private:
  void LabelAndDelaySetter();
  void WindowSetter();
  void InitExtraInfoScene();

  bool IsEndState() { return state_ == S::GAME_OVER || state_ == S::WIN; }
  void DrawField();
  void DrawExtraScene();
  size_t GetExtraSceneXOffset(std::vector<std::pair<int, int>> &info);
  void OffAddInfo();

  using dirs = S21Directions;
  dirs KeysConvert();
  void SymbolHandle(const char c, const int y, const int x, const int wx);
  void EndGame();
  void PrintEndGame();

 private:
  std::map<Keys, dirs> keys_to_dir_ = {{Keys::UP, UP},
                                       {Keys::DOWN, DOWN},
                                       {Keys::LEFT, LEFT},
                                       {Keys::RIGHT, RIGHT},
                                       {Keys::ACTION, ACTION}};
};

}  // namespace s21

#include "s21_desktop_view.tpp"
#endif
