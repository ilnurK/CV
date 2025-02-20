#include "s21_bg_window.h"

#include <QFontDatabase>

#include "s21_desktop_view.h"
#include "s21_resized_view.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BrickGamesWindow) {
  ui->setupUi(this);
  view_ = ui->graphics_view;
  view_->WindowSetup(this);
  extra_view_ = ui->extra_view;
  view_width_ = view_->viewport()->width();
  view_height_ = view_->viewport()->height();
  scene_.reset(new QGraphicsScene(scene_rect_, this));
  view_->setScene(scene_.data());
  InitCarousel();
  //    ButtonsInit();
  ui->next_label->setVisible(false);
  ui->speed_label->setVisible(false);
  ui->pause_label->setStyleSheet("color: grey");
  QFontDatabase::addApplicationFont(font_path_);
  this->setFocusPolicy(Qt::StrongFocus);
  this->setFocus();
}

void MainWindow::InitCarousel() {
  ImageInit(snake_game_cover_, snake_game_path_);
  ImageInit(tetris_game_cover_, tetris_game_path_);
  ImageInit(race_game_cover_, race_game_path_);
  game_ = Games::SNAKE;
  snake_game_cover_->setVisible(true);
}

void MainWindow::ImageInit(QSharedPointer<QGraphicsPixmapItem> &image,
                           const QString file) {
  image.reset(new QGraphicsPixmapItem(QPixmap(file)));
  const int image_size{image->pixmap().size().width()};
  image->setScale(static_cast<double>(view_width_) / image_size);
  scene_->addItem(image.data());
  image->setVisible(false);
  covers_.push_back(image);
}

void MainWindow::PlayView() {
  this->setFocus();
  game_view_->Play();
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

void MainWindow::SetSpeed(size_t speed) {
  const QString value_text{QString::fromStdString(std::to_string(speed))};
  ui->speed_label->setText(speed_text_ + value_text);
}

Keys MainWindow::GetKey() {
  Keys res{Keys::KEY_NULL};
  if (key_cr_ < key_list_.size()) {
    auto it = key_list_.begin();
    std::advance(it, key_cr_);
    res = *it;
    key_cr_ += 1;
  }
  return res;
}

void MainWindow::LabelNull() {
  ui->score_label->setText(score_text_);
  ui->highscore_label->setText(highscore_text_);
  ui->level_label->setText(level_text_);
  ui->speed_label->setText(speed_text_);
  ui->pause_label->setStyleSheet("color: grey");
}

MainWindow::~MainWindow() {
  delete ui;
  if (game_view_) {
    delete game_view_;
  }
}

void MainWindow::on_graphics_view_destroyed() { ; }

}  // namespace s21
