#include "s21_resized_view.h"

#include "s21_bg_window.h"

namespace s21 {

void ResizedView::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);

  double h = parentWidget()->height(), w = parentWidget()->width();
  if (w * 2 > h) {
    resize(h / 2, h);
  } else {
    resize(w, w * 2);
  }
  fitInView(window_->GetSceneRect(), Qt::IgnoreAspectRatio);
}

}  // namespace s21
