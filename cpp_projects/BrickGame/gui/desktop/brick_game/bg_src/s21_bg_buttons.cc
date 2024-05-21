#include "s21_bg_window.h"
#include "ui_s21_bg_window.h"

namespace s21 {

void MainWindow::ButtonsInit() {
  left_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Left), this));
  connect(left_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_left_button_clicked);

  right_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Right), this));
  connect(right_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_right_button_clicked);

  up_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Up), this));
  connect(up_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_up_button_clicked);

  down_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Down), this));
  connect(down_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_down_button_clicked);

  space_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Space), this));
  connect(space_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_action_button_clicked);

  start_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_P), this));
  connect(start_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_start_button_clicked);

  quit_shortcut_.reset(new QShortcut(QKeySequence(Qt::Key_Q), this));
  connect(quit_shortcut_.data(), &QShortcut::activated, this,
          &MainWindow::on_quit_button_clicked);
}

void MainWindow::on_start_button_clicked() {
  if (!is_playing_) {
    key_list_.clear();

    if (game_ == Games::SNAKE) {
      snake_view_.reset();
      snake_view_.reset(new SnakeView(this));
      game_timer_.reset(new QTimer(this));
      QObject::connect(game_timer_.data(), &QTimer::timeout, this,
                       &MainWindow::DrawSnakeView);
      game_timer_->start();
    } else if (game_ == Games::TETRIS) {
      tetris_view_.reset();
      tetris_view_.reset(new TetrisView(this));
      game_timer_.reset(new QTimer(this));
      QObject::connect(game_timer_.data(), &QTimer::timeout, this,
                       &MainWindow::DrawTetrisView);
      game_timer_->start();
    }
  } else {
    if (key_list_.back() == Keys::PAUSE) {
      Unpausing();
    } else {
      key_list_.clear();
      key_list_.push_back(Keys::PAUSE);
      ui->pause_label->setStyleSheet("color: black");
    }
  }
}

void MainWindow::Unpausing() {
  key_list_.clear();
  ui->pause_label->setStyleSheet("color: grey");
}

void MainWindow::on_left_button_clicked() {
  if (is_playing_) {
    if (key_list_.front() != Keys::PAUSE) {
      key_list_.push_back(Keys::LEFT);
    }
  } else if (game_ == Games::SNAKE) {
    game_ = Games::TETRIS;
    snake_game_cover_->setVisible(false);
    tetris_game_cover_->setVisible(true);
  } else {
    game_ = Games::SNAKE;
    snake_game_cover_->setVisible(true);
    tetris_game_cover_->setVisible(false);
  }
}

void MainWindow::on_down_button_clicked() {
  if (key_list_.front() != Keys::PAUSE) {
    if (game_ == Games::TETRIS) {
      key_list_.clear();
    }
    key_list_.push_back(Keys::DOWN);
  }
}

void MainWindow::on_right_button_clicked() {
  if (is_playing_) {
    if (key_list_.front() != Keys::PAUSE) {
      key_list_.push_back(Keys::RIGHT);
    }
  } else if (game_ == Games::SNAKE) {
    game_ = Games::TETRIS;
    snake_game_cover_->setVisible(false);
    tetris_game_cover_->setVisible(true);
  } else {
    game_ = Games::SNAKE;
    snake_game_cover_->setVisible(true);
    tetris_game_cover_->setVisible(false);
  }
}

void MainWindow::on_up_button_clicked() {
  if (key_list_.front() != Keys::PAUSE && game_ != Games::TETRIS) {
    key_list_.push_back(Keys::UP);
  }
}

void MainWindow::on_action_button_clicked() {
  if (key_list_.front() == Keys::ACTION) {
    key_list_.clear();
  }
  key_list_.push_back(Keys::ACTION);
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
  Unpausing();
  game_timer_->stop();
  if (game_ == Games::SNAKE) {
    snake_view_.reset();
  } else if (game_ == Games::TETRIS) {
    tetris_view_.reset();
  }
  LabelNull();
}

}  // namespace s21
