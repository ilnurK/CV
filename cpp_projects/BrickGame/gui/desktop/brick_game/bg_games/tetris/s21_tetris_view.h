#ifndef S21_BRICK_GAME_TETRIS_VIEW_H
#define S21_BRICK_GAME_TETRIS_VIEW_H

#include <QGraphicsScene>
#include <QObject>

extern "C" {
#include "../../../../../brick_game/tetris_c/s21_tetris_controller.h"
}

namespace s21 {

class MainWindow;

class TetrisView {
 private:
  MainWindow* window_;
  QScopedPointer<QGraphicsScene> tetris_scene_{};
  QScopedPointer<QGraphicsScene> nf_scene_{};

 private:
  S21TetrisController* tetris_ctrl_;
  S21TetrisStates state_;
  S21TetrisError error_;
  size_t margin_{2};
  size_t state_speed_{600};
  size_t score_{};
  size_t highscore_{};
  QScopedPointer<QGraphicsTextItem> end_text_;

 public:
  TetrisView(MainWindow* window_in);
  ~TetrisView();

 public:
  void DrawState();

 private:
  void ScoreCheck(size_t old_score, size_t old_level);
  void DrawField();
  void DrawNextFigure();
  void InitNextFigureScene();
  void TetrisEndGame();
};

}  // namespace s21

#

#endif
