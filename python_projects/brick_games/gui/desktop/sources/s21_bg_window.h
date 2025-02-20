#ifndef S21_BG_WINDOW_H
#define S21_BG_WINDOW_H

#include <Python.h>

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QVector>
#include <list>

#include "s21_bg_keys.h"
#include "ui_s21_bg_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class BrickGamesWindow;
}
QT_END_NAMESPACE

namespace s21 {

enum class Games { NULL_GAME, SNAKE, TETRIS, RACE };

class ResizedView;

class DesktopViewBase;

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  DesktopViewBase *game_view_{};
  QScopedPointer<QTimer> game_timer_{};

 private:
  Games game_{};
  Keys key_{};
  std::list<Keys> key_list_{};
  bool is_playing_{};
  bool is_sound_{};

 private:
  ResizedView *view_{};
  QGraphicsView *extra_view_{};
  int view_width_{}, view_height_{};
  QScopedPointer<QGraphicsScene> scene_{};
  QRectF scene_rect_{0, 0, 100, 200};
  size_t max_keys_ = 3;
  size_t key_cr_ = 0;

 private:
  Ui::BrickGamesWindow *ui;

 private:
  const QString font_name_{"LAB Grotesk"};
  const QString font_path_{":/lab-grotesk.ttf"};
  const QString score_text_{"SCORE\n"};
  const QString highscore_text_{"HIGHSCORE\n"};
  const QString level_text_{"LEVEL\n"};
  const QString speed_text_{"SPEED\n"};

 private:
  QSharedPointer<QGraphicsPixmapItem> snake_game_cover_{};
  const QString snake_game_path_{":/snake_game.png"};
  QSharedPointer<QGraphicsPixmapItem> tetris_game_cover_{};
  const QString tetris_game_path_{":/tetris_game.png"};
  QSharedPointer<QGraphicsPixmapItem> race_game_cover_{};
  const QString race_game_path_{":/race_game.png"};
  QVector<QSharedPointer<QGraphicsPixmapItem>> covers_{};

 private slots:
  void on_start_button_clicked();
  void pause_clicked();
  void on_sound_button_clicked();
  void on_quit_button_clicked();
  void on_reset_button_clicked();

  void on_graphics_view_destroyed();

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void PlayView();

  void on_left_button_pressed();
  void on_up_button_pressed();
  void on_right_button_pressed();
  void on_down_button_pressed();
  void on_action_button_pressed();

  void on_left_button_released();
  void on_up_button_released();
  void on_right_button_released();
  void on_down_button_released();
  void on_action_button_released();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 public:
  QGraphicsScene *GetScene() { return scene_.data(); }
  ResizedView *GetView() { return view_; }
  QGraphicsView *GetExtraView() { return extra_view_; }
  int GetViewWidth() { return view_width_; }
  int GetViewHeight() { return view_height_; }
  Keys GetKey();
  QTimer *GetTimer() { return game_timer_.data(); }
  const QString GetFontName() const { return font_name_; }
  const QRectF GetSceneRect() const { return scene_rect_; }
  bool GetPlayingStatus() const { return is_playing_; }

 public:
  void SetPlayingStatus(bool is_playing) { is_playing_ = is_playing; }
  void SetKey(Keys key) { key_ = key; }
  void SetScore(size_t score);
  void SetHighScore(size_t highscore);
  void SetLevel(size_t level);
  void SetSpeed(size_t speed);
  void SetExtraViewVisible(bool val) { extra_view_->setVisible(val); }
  void ExtraLabelsHandle();
  void LabelNull();
  void KeyAdd(Keys key);
  void ReleaseKey();

 private:
  void InitCarousel();

  void CarouselChooser(bool is_right = true);
  void ImageInit(QSharedPointer<QGraphicsPixmapItem> &image,
                 const QString file);
};

}  // namespace s21
#endif  // S21_BG_WINDOW_H
