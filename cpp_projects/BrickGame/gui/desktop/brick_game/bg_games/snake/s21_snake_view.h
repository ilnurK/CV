#ifndef S21_BRICK_GAMES_SNAKE_VIEW_H
#define S21_BRICK_GAMES_SNAKE_VIEW_H

#include <QGraphicsOpacityEffect>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QVector>

#include "../../../../../brick_game/snake/s21_snake_controller.h"

namespace s21 {

class MainWindow;
enum class Keys;

class SnakeView {
 private:
  MainWindow *window_;
  QScopedPointer<QGraphicsScene> snake_scene_{};
  double pixel_size_;

 private:
  std::unique_ptr<SnakeController> snake_ctrl_;
  GameStatus status_;
  size_t highscore_{};

 private:
  size_t standart_time_step_{1000};
  size_t time_step_{1000};

 private:
  const QString images_folder_{":"};
  const QString apple_file_{images_folder_ + "/apple.png"};
  const QString snake_head_file_{images_folder_ + "/snake_head.png"};
  const QString snake_body_file_{images_folder_ + "/snake_body.png"};
  const QString snake_tail_file_{images_folder_ + "/snake_tail.png"};
  QScopedPointer<QGraphicsPixmapItem> apple_image_{};
  QScopedPointer<QGraphicsPixmapItem> snake_head_image_{};
  QScopedPointer<QGraphicsPixmapItem> snake_tail_image_{};
  size_t snake_body_image_size_{};
  QVector<QSharedPointer<QGraphicsPixmapItem>> snake_body_parts_{};

 private:
  QGraphicsOpacityEffect *anim_effect_{};
  QPropertyAnimation *anim_{};
  QSharedPointer<QGraphicsPixmapItem> end_game_image_;
  QSharedPointer<QGraphicsPixmapItem> end_game_anim_image_;
  const QString game_over_file_{images_folder_ + "/game_over.png"};
  const QString game_over_eyes_file_{images_folder_ + "/game_over_eyes.png"};
  const QString win_file_{images_folder_ + "/win.png"};
  const QString win_tongue_file_{images_folder_ + "/win_tongue.png"};

 public:
  SnakeView(MainWindow *window_in);
  ~SnakeView();

 private:
  void ImagesInit();
  void ImageInit(QScopedPointer<QGraphicsPixmapItem> &image,
                 const QString file);
  void SceneAddSnakeBody();
  void SetApple();
  void SetSnake(const size_t snake_size);
  void RotateImage(QGraphicsPixmapItem *image, Dirs &dir, xy_pair it);
  Dirs GetLastBodyPartDir(xy_pair tail_xy, size_t snake_size);
  void SpeedCorrecting(const Keys &key);
  void PrintEndGame();

 public:
  void DrawState();
};

}  // namespace s21

#endif
