#include "widget.h"

namespace s21 {

void CustomGLWidget::mousePressEvent(QMouseEvent *event) {
  // Получаем начальные координаты мыши
  last_pos = event->pos();
}

void CustomGLWidget::mouseMoveEvent(QMouseEvent *event) {
  // Вычисляем смещение мыши относительно начальных координат
  int dx = event->x() - last_pos.x();
  int dy = event->y() - last_pos.y();

  // Обновляем начальные координаты мыши
  last_pos = event->pos();

  emit mouseMoved(dx, dy);
}

void CustomGLWidget::wheelEvent(QWheelEvent *event) {
  // Получаем угол прокрутки колесика мыши
  int numDegrees = event->angleDelta().y() / 8;
  emit wheelDeltaChanged(numDegrees);
}

}  // namespace s21
