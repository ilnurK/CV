#ifndef S21_BG_WINDOW_H
#define S21_BG_WINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <list>

#include "../bg_games/snake/s21_snake_view.h"
#include "../bg_games/tetris/s21_tetris_view.h"
#include "ui_s21_bg_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class BrickGamesWindow;
}
QT_END_NAMESPACE

namespace s21 {

enum class Games { NULL_GAME, SNAKE, TETRIS };

class SnakeView;
class ResizedView;

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Games game_{};
  Keys key_{};
  std::list<Keys> key_list_{};
  bool is_playing_{};
  bool is_sound_{};
  ResizedView *view_{};
  QGraphicsView *nf_view_{};
  int view_width_{}, view_height_{};
  QScopedPointer<QGraphicsScene> scene_{};
  QRectF scene_rect_{0, 0, 100, 200};

 private:
  QScopedPointer<QShortcut> start_shortcut_{};
  QScopedPointer<QShortcut> left_shortcut_{};
  QScopedPointer<QShortcut> right_shortcut_{};
  QScopedPointer<QShortcut> up_shortcut_{};
  QScopedPointer<QShortcut> down_shortcut_{};
  QScopedPointer<QShortcut> space_shortcut_{};
  QScopedPointer<QShortcut> quit_shortcut_{};

 private:
  QScopedPointer<SnakeView> snake_view_{};
  QScopedPointer<TetrisView> tetris_view_{};
  QScopedPointer<QTimer> game_timer_{};
  size_t tetris_max_keys_ = 3;
  size_t snake_max_keys_ = 3;

 private:
  Ui::BrickGamesWindow *ui;

 private:
  const QString font_name_{"LAB Grotesk"};
  const QString font_path_{":/lab-grotesk.ttf"};
  const QString score_text_{"SCORE\n"};
  const QString highscore_text_{"HIGHSCORE\n"};
  const QString level_text_{"LEVEL\n"};

 private:
  QScopedPointer<QGraphicsPixmapItem> snake_game_cover_{};
  const QString snake_game_path_{":/snake_game.png"};
  QScopedPointer<QGraphicsPixmapItem> tetris_game_cover_{};
  const QString tetris_game_path_{":/tetris_game.png"};

 private slots:
  void DrawSnakeView();
  void DrawTetrisView();

 private slots:
  void on_start_button_clicked();
  void on_left_button_clicked();
  void on_down_button_clicked();
  void on_right_button_clicked();
  void on_up_button_clicked();
  void on_action_button_clicked();
  void on_quit_button_clicked();
  void on_sound_button_clicked();
  void on_reset_button_clicked();
  void on_graphics_view_destroyed();

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public:
  QGraphicsScene *GetScene() { return scene_.data(); }
  ResizedView *GetView() { return view_; }
  QGraphicsView *GetNFView() { return nf_view_; }
  int GetViewWidth() { return view_width_; }
  int GetViewHeight() { return view_height_; }
  SnakeView *GetSnakeView() { return snake_view_.data(); }
  Keys GetKey();
  QTimer *GetTimer() { return game_timer_.data(); }
  const QString GetFontName() const { return font_name_; }
  const QRectF GetSceneRect() const { return scene_rect_; }
  void LabelNull();

 public:
  void SetPlayingStatus(bool is_playing) { is_playing_ = is_playing; }
  void SetKey(Keys key) { key_ = key; }
  void SetScore(size_t score);
  void SetHighScore(size_t highscore);
  void SetLevel(size_t level);
  void SetNextFigureVisible(bool val) { nf_view_->setVisible(val); }

 public:
  void ClearKeyList();

 private:
  void InitCarousel();
  void ButtonsInit();
  void SoundInit();
  void ImageInit(QScopedPointer<QGraphicsPixmapItem> &image,
                 const QString file);
  void Unpausing();
};

}  // namespace s21
#endif  // S21_BG_WINDOW_H
