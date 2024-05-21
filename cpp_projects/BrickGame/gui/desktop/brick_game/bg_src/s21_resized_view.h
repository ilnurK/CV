#ifndef S21_BRICK_GAME_RESIZED_VIEW_H
#define S21_BRICK_GAME_RESIZED_VIEW_H

#include <QGraphicsView>

namespace s21 {

class MainWindow;

class ResizedView : public QGraphicsView {
  Q_OBJECT

 private:
  MainWindow* window_;

 public:
  ResizedView(QWidget* parent = nullptr) : QGraphicsView(parent) {}

 protected:
  void resizeEvent(QResizeEvent* event) override;

 public:
  void WindowSetup(MainWindow* window_in) { window_ = window_in; }
};

}  // namespace s21

#endif
