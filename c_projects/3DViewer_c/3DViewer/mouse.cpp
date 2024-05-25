#include "widget.h"

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  // Получаем начальные координаты мыши
  lastPos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  // Вычисляем смещение мыши относительно начальных координат
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  // Обновляем начальные координаты мыши
  lastPos = event->pos();

  emit mouseMoved(dx, dy);
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  // Получаем угол прокрутки колесика мыши
  int numDegrees = event->angleDelta().y() / 8;
  emit wheelDeltaChanged(numDegrees);
}
