#include "s21_bg_window.h"

#include <QFile>
#include <QFontDatabase>

#include "s21_resized_view.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BrickGamesWindow) {
  ui->setupUi(this);
  view_ = ui->graphics_view;
  view_->WindowSetup(this);
  nf_view_ = ui->next_figure_view;
  view_width_ = view_->viewport()->width();
  view_height_ = view_->viewport()->height();
  scene_.reset(new QGraphicsScene(scene_rect_, this));
  view_->setScene(scene_.data());
  InitCarousel();
  ButtonsInit();
  ui->pause_label->setStyleSheet("color: grey");
  QFontDatabase::addApplicationFont(font_path_);
}

void MainWindow::InitCarousel() {
  ImageInit(snake_game_cover_, snake_game_path_);
  ImageInit(tetris_game_cover_, tetris_game_path_);
  game_ = Games::SNAKE;
  tetris_game_cover_->setVisible(false);
}

void MainWindow::ImageInit(QScopedPointer<QGraphicsPixmapItem> &image,
                           const QString file) {
  image.reset(new QGraphicsPixmapItem(QPixmap(file)));
  const int image_size{image->pixmap().size().width()};
  image->setScale(static_cast<double>(view_width_) / image_size);
  scene_->addItem(image.data());
}

void MainWindow::DrawSnakeView() {
  while (key_list_.size() > snake_max_keys_) {
    key_list_.pop_front();
  }
  snake_view_->DrawState();
}

void MainWindow::DrawTetrisView() {
  while (key_list_.size() > tetris_max_keys_) {
    key_list_.pop_front();
  }
  tetris_view_->DrawState();
}

void MainWindow::SetScore(size_t score) {
  const QString value_text{QString::fromStdString(std::to_string(score))};
  ui->score_label->setText(score_text_ + value_text);
}

void MainWindow::SetHighScore(size_t highscore) {
  const QString value_text{QString::fromStdString(std::to_string(highscore))};
  ui->highscore_label->setText(highscore_text_ + value_text);
}

void MainWindow::SetLevel(size_t level) {
  const QString value_text{QString::fromStdString(std::to_string(level))};
  ui->level_label->setText(level_text_ + value_text);
}

Keys MainWindow::GetKey() {
  Keys res{key_list_.front()};
  if (key_list_.size() && res != Keys::PAUSE) {
    key_list_.pop_front();
  }
  return res;
}

void MainWindow::ClearKeyList() {
  while (key_list_.size()) {
    key_list_.pop_back();
  }
}

void MainWindow::LabelNull() {
  ui->score_label->setText(score_text_);
  ui->highscore_label->setText(highscore_text_);
  ui->level_label->setText(level_text_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_graphics_view_destroyed() { ; }

}  // namespace s21
