#include "s21_bg_window.h"
#include "s21_desktop_view.h"
#include "ui_s21_bg_window.h"

namespace s21 {

void MainWindow::on_start_button_clicked() {
  if (!is_playing_) {
    if (game_view_) {
      on_reset_button_clicked();
    }
    if (game_ == Games::SNAKE) {
      game_view_ = new DesktopView<SnakeController, SnakeStates>(this);
    } else if (game_ == Games::TETRIS) {
      game_view_ = new DesktopView<TetrisController, S21TetrisStates>(this);
    } else if (game_ == Games::RACE) {
      game_view_ = new DesktopView<RaceCController, RaceStates>(this);
    }
    game_timer_.reset(new QTimer(this));
    QObject::connect(game_timer_.data(), &QTimer::timeout, this,
                     &MainWindow::PlayView);
    game_timer_->start();
    is_playing_ = true;
  }
}

void MainWindow::pause_clicked() {
  if (game_view_ && game_view_->IsPause()) {
    ui->pause_label->setStyleSheet("color: grey");
  } else {
    ui->pause_label->setStyleSheet("color: black");
  }
  key_ = Keys::PAUSE;
}

void MainWindow::on_sound_button_clicked() {
  if (!is_sound_) {
    is_sound_ = true;
    ui->note_label->setStyleSheet("color: grey");
  } else {
    is_sound_ = false;
    ui->note_label->setStyleSheet("color: black");
  }
}

void MainWindow::on_quit_button_clicked() { close(); }

void MainWindow::on_reset_button_clicked() {
  is_playing_ = false;
  view_->setScene(scene_.data());
  if (game_timer_ && game_timer_->isActive()) {
    game_timer_->stop();
  }
  delete game_view_;
  game_view_ = nullptr;
  LabelNull();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    emit ui->up_button->pressed();
  } else if (key == Qt::Key_Right) {
    emit ui->right_button->pressed();
  } else if (key == Qt::Key_Down) {
    emit ui->down_button->pressed();
  } else if (key == Qt::Key_Left) {
    emit ui->left_button->pressed();
  } else if (key == Qt::Key_Space) {
    emit ui->action_button->pressed();
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    emit ui->up_button->released();
  } else if (key == Qt::Key_Right) {
    emit ui->right_button->released();
  } else if (key == Qt::Key_Down) {
    emit ui->down_button->released();
  } else if (key == Qt::Key_Left) {
    emit ui->left_button->released();
  } else if (key == Qt::Key_Space) {
    emit ui->action_button->released();
  } else if (key == Qt::Key_Q) {
    on_quit_button_clicked();
  } else if (key == Qt::Key_P) {
    pause_clicked();
    KeyAdd(Keys::PAUSE);
  } else if (key == Qt::Key_S) {
    on_start_button_clicked();
  }
}

void MainWindow::KeyAdd(Keys key) {
  if (key_list_.size() < max_keys_) {
    if (!key_list_.empty()) {
      key_list_.pop_front();
    }
    key_list_.push_back(key);
    key_cr_ -= (key_cr_) ? 1 : 0;
  }
}

void MainWindow::on_left_button_pressed() {
  if (is_playing_) {
    KeyAdd(Keys::LEFT);
  } else {
    bool is_right = false;
    CarouselChooser(is_right);
  }
}

void MainWindow::on_right_button_pressed() {
  if (is_playing_) {
    KeyAdd(Keys::RIGHT);
  } else {
    bool is_right = true;
    CarouselChooser(is_right);
  }
}

void MainWindow::on_up_button_pressed() {
  if (game_ != Games::TETRIS) {
    KeyAdd(Keys::UP);
  }
}
void MainWindow::on_down_button_pressed() { KeyAdd(Keys::DOWN); }
void MainWindow::on_action_button_pressed() { KeyAdd(Keys::ACTION); }

void MainWindow::ReleaseKey() { ; }

void MainWindow::on_left_button_released() { ReleaseKey(); }
void MainWindow::on_up_button_released() { ReleaseKey(); }
void MainWindow::on_right_button_released() { ReleaseKey(); }
void MainWindow::on_down_button_released() { ReleaseKey(); }
void MainWindow::on_action_button_released() { ReleaseKey(); }

void MainWindow::CarouselChooser(bool is_right) {
  for (const auto &cover : covers_) {
    if (cover) {
      cover->setVisible(false);
    }
  }

  if (game_ == Games::RACE) {
    if (is_right) {
      game_ = Games::TETRIS;
      tetris_game_cover_->setVisible(true);
    } else {
      game_ = Games::SNAKE;
      snake_game_cover_->setVisible(true);
    }
  } else if (game_ == Games::SNAKE) {
    if (is_right) {
      game_ = Games::RACE;
      race_game_cover_->setVisible(true);
    } else {
      game_ = Games::TETRIS;
      tetris_game_cover_->setVisible(true);
    }

  } else if (game_ == Games::TETRIS) {
    if (is_right) {
      game_ = Games::SNAKE;
      snake_game_cover_->setVisible(true);
    } else {
      game_ = Games::RACE;
      race_game_cover_->setVisible(true);
    }
  }
  ExtraLabelsHandle();
}

void MainWindow::ExtraLabelsHandle() {
  ui->speed_label->setVisible(false);
  ui->next_label->setVisible(false);
  if (game_ == Games::RACE) {
    ui->speed_label->setVisible(true);
  } else if (game_ == Games::TETRIS) {
    ui->next_label->setVisible(true);
  }
}

}  // namespace s21
