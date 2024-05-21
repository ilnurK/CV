#include "s21_snake_view.h"

#include "../../bg_src/s21_bg_window.h"

namespace s21 {

SnakeView::SnakeView(MainWindow *window_in)
    : window_(window_in), snake_ctrl_(std::make_unique<SnakeController>()) {
  status_ = GameStatus::ON_AIR;
  snake_scene_.reset(new QGraphicsScene(window_->GetSceneRect(), nullptr));
  window_->GetView()->setScene(snake_scene_.data());
  pixel_size_ = snake_ctrl_->width;
  highscore_ = snake_ctrl_->GetHighScore();
  window_->SetPlayingStatus(true);
  snake_scene_->clear();
  window_->SetScore(snake_ctrl_->GetScore());
  window_->SetHighScore(highscore_);
  window_->SetLevel(snake_ctrl_->GetLevel());

  ImagesInit();
  SetApple();
}

void SnakeView::ImagesInit() {
  ImageInit(apple_image_, apple_file_);
  ImageInit(snake_head_image_, snake_head_file_);
  ImageInit(snake_tail_image_, snake_tail_file_);

  QScopedPointer<QGraphicsPixmapItem> snake_body_image(
      new QGraphicsPixmapItem(QPixmap(snake_body_file_)));
  snake_body_image_size_ = snake_body_image->pixmap().size().width();
  size_t i = snake_ctrl_->GetSnake().size(), head_and_tail = 2;
  while (i-- > head_and_tail) {
    SceneAddSnakeBody();
  }
}

void SnakeView::ImageInit(QScopedPointer<QGraphicsPixmapItem> &image,
                          const QString file) {
  image.reset(new QGraphicsPixmapItem(QPixmap(file)));
  const int image_size = image->pixmap().size().width();
  image->setScale(pixel_size_ / image_size);
  snake_scene_->addItem(image.data());
}

void SnakeView::SceneAddSnakeBody() {
  snake_body_parts_.emplace_back(QSharedPointer<QGraphicsPixmapItem>(
      new QGraphicsPixmapItem(QPixmap(snake_body_file_))));

  snake_body_parts_.back()->setScale(pixel_size_ / snake_body_image_size_);
  snake_scene_->addItem(snake_body_parts_.back().data());
}

void SnakeView::DrawState() {
  size_t old_snake_size{snake_ctrl_->GetSnakeSize()};
  Keys key = window_->GetKey();
  if (key == Keys::NULL_KEY || key == Keys::ACTION) {
    status_ = snake_ctrl_->SetState(SnakeStates::MOVING);
  } else if (key < Keys::ACTION) {
    status_ =
        snake_ctrl_->SetState(SnakeStates::SHIFTING, static_cast<Dirs>(key));
  }

  size_t snake_size{snake_ctrl_->GetSnakeSize()};
  if (old_snake_size < snake_size) {
    SceneAddSnakeBody();
    SetApple();
    old_snake_size = snake_size;
    size_t score = snake_ctrl_->GetScore();
    window_->SetScore(score);
    if (score > highscore_) {
      window_->SetHighScore(score);
    }
  }
  if (key != Keys::PAUSE) {
    SetSnake(snake_size);
    SpeedCorrecting(key);
    window_->GetTimer()->start(time_step_);
    if (status_ == GameStatus::WIN || status_ == GameStatus::GAME_OVER) {
      window_->GetTimer()->stop();
      PrintEndGame();
      window_->SetPlayingStatus(false);
    }
  }
}

void SnakeView::SetApple() {
  auto [apple_x, apple_y] = snake_ctrl_->GetApple();
  if (!apple_image_) {
    throw std::invalid_argument("apple_image_ doesn't exist");
  }
  apple_image_->setPos(apple_x * pixel_size_, apple_y * pixel_size_);
}

void SnakeView::SetSnake(const size_t snake_size) {
  size_t idx = 0, head_idx = 0, tail_idx = snake_size - 1;
  Dirs dir = snake_ctrl_->GetDirection();
  for (auto it : snake_ctrl_->GetSnake()) {
    if (idx == head_idx) {
      RotateImage(snake_head_image_.data(), dir, it);
    } else if (idx == tail_idx) {
      dir = GetLastBodyPartDir(it, snake_size);
      RotateImage(snake_tail_image_.data(), dir, it);
    } else {
      (snake_body_parts_[idx - 1])
          ->setPos(it.first * pixel_size_, it.second * pixel_size_);
    }
    idx++;
  }
}

Dirs SnakeView::GetLastBodyPartDir(xy_pair tail_xy, size_t snake_size) {
  Dirs dir{};
  xy_pair last_xy{snake_ctrl_->GetSnake()[snake_size - 2]};
  if (last_xy.first > tail_xy.first) {
    dir = Dirs::RIGHT;
  } else if (last_xy.first < tail_xy.first) {
    dir = Dirs::LEFT;
  } else if (last_xy.second < tail_xy.second) {
    dir = Dirs::UP;
  } else if (last_xy.second > tail_xy.second) {
    dir = Dirs::DOWN;
  }
  return dir;
}

void SnakeView::RotateImage(QGraphicsPixmapItem *image, Dirs &dir, xy_pair it) {
  if (!image) {
    throw std::invalid_argument("snake_image doesn't exist");
  }
  if (dir == Dirs::UP) {
    image->setRotation(0);
    image->setPos(it.first * pixel_size_, it.second * pixel_size_);
  } else if (dir == Dirs::RIGHT) {
    image->setRotation(90);
    image->setPos(it.first * pixel_size_ + pixel_size_,
                  it.second * pixel_size_);
  } else if (dir == Dirs::DOWN) {
    image->setRotation(180);
    image->setPos(it.first * pixel_size_ + pixel_size_,
                  it.second * pixel_size_ + pixel_size_);
  } else if (dir == Dirs::LEFT) {
    image->setRotation(270);
    image->setPos(it.first * pixel_size_,
                  it.second * pixel_size_ + pixel_size_);
  }
}

void SnakeView::SpeedCorrecting(const Keys &key) {
  if (status_ == GameStatus::LEVEL_UP) {
    standart_time_step_ *= 0.8;
    window_->SetLevel(snake_ctrl_->GetLevel());
  }
  if (key == Keys::ACTION) {
    time_step_ = standart_time_step_ / 5;
  } else {
    time_step_ = standart_time_step_;
  }
}

void SnakeView::PrintEndGame() {
  if (status_ == GameStatus::WIN) {
    end_game_image_.reset(new QGraphicsPixmapItem(QPixmap(win_file_)));
    end_game_anim_image_.reset(
        new QGraphicsPixmapItem(QPixmap(win_tongue_file_)));
  } else {
    end_game_image_.reset(new QGraphicsPixmapItem(QPixmap(game_over_file_)));
    end_game_anim_image_.reset(
        new QGraphicsPixmapItem(QPixmap(game_over_eyes_file_)));
  }
  const double image_width = end_game_image_->pixmap().width();
  const double scale_factor = window_->GetSceneRect().width() / image_width;
  end_game_image_->setScale(scale_factor);
  const QPointF image_pos = {
      0, window_->GetSceneRect().height() / 2 - image_width * scale_factor / 2};
  end_game_image_->setPos(image_pos);
  for (QGraphicsItem *item : snake_scene_->items()) {
    item->setVisible(false);
  }

  snake_scene_->addItem(end_game_image_.data());

  end_game_anim_image_->setScale(scale_factor);
  end_game_anim_image_->setPos(image_pos);
  snake_scene_->addItem(end_game_anim_image_.data());

  anim_effect_ = new QGraphicsOpacityEffect(snake_scene_.data());
  anim_ = new QPropertyAnimation(anim_effect_, "opacity");

  end_game_anim_image_->setGraphicsEffect(anim_effect_);
  anim_->setStartValue(1.0);
  anim_->setEndValue(0.0);
  anim_->setDuration(1000);
  QObject::connect(anim_, &QPropertyAnimation::finished, [=]() {
    anim_->setDirection(anim_->direction() == QAbstractAnimation::Forward
                            ? QAbstractAnimation::Backward
                            : QAbstractAnimation::Forward);
    anim_->start();
  });
  anim_->start();
}

SnakeView::~SnakeView() {
  if (snake_ctrl_->GetScore() > highscore_) {
    snake_ctrl_->WriteScore();
  }
  delete anim_;
  delete anim_effect_;
}

}  // namespace s21
