#include "widget.h"

#include "gif.h"

namespace s21 {

CustomGLWidget::CustomGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void CustomGLWidget::initializeGL() {
  initializeOpenGLFunctions();  // Инициализация функций OpenGL
  glEnable(GL_DEPTH_TEST);  // Включение буфера глубины
}

void CustomGLWidget::paintGL() {
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(),
               background_color.alphaF());  // Заливка фона
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Очистка экрана

  // Настройка типа проекции
  int width = this->width();
  int height = this->height();
  double coefficient = (double)width / (double)height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (settings.projection_type == 0) {
    glOrtho(-coefficient, coefficient, -1, 1, -coefficient * 3,
            coefficient * 3);
  } else if (settings.projection_type == 1) {
    gluPerspective(45.0, coefficient, 0.01, 100.0);
    glTranslatef(0, 0, -3);
  }

  // Настройка типа линий рёбер
  if (settings.type == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else if (settings.type == 1) {  // для пунктирных линий
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(5, 0x8888);
  }
  // Настройка толщины ребер
  glLineWidth(settings.thickness);
  // Настройка цвета ребер
  glColor3f(settings.color_edges.redF(), settings.color_edges.greenF(),
            settings.color_edges.blueF());

  DrawModel(0);

  // Настройка вида вершин
  if (settings.display_method != 0) {
    glPointSize(settings.size);
    settings.display_method == 1 ? glEnable(GL_POINT_SMOOTH)
                                 : glDisable(GL_POINT_SMOOTH);
    glColor3f(settings.color_vertices.redF(), settings.color_vertices.greenF(),
              settings.color_vertices.blueF());
    DrawModel(1);
  }
}

void CustomGLWidget::DrawModel(int mode) {
  if (viewer_ctrl_) {
    ViewerErrors error = viewer_ctrl_->GetError();
    if (error == ViewerErrors::ALL_OK) {
      const std::vector<double> &indices = viewer_ctrl_->GetIndices();
      size_t surfaces = indices.size();
      size_t row_start{0}, row_end{0};
      bool flag_end{false};
      while (!flag_end && error == ViewerErrors::ALL_OK) {
        (mode == 0) ? glBegin(GL_LINE_LOOP) : glBegin(GL_POINTS);
        DrawCycle(indices, flag_end, row_start, row_end, surfaces);
        error = viewer_ctrl_->GetError();
        glEnd();
      }
    }
  }
}

void CustomGLWidget::DrawCycle(const std::vector<double> &indices,
                               bool &flag_end, size_t &start, size_t &end,
                               const size_t surfaces) {
  start = end + 1;
  if (surfaces && end < surfaces - 1) {
    size_t verts_in_surf = indices[end];
    end = start + verts_in_surf;
    for (size_t i = start; i < end; i++) {
      size_t vertex = indices[i] - 1;
      glVertex3d(viewer_ctrl_->At(vertex, 0), viewer_ctrl_->At(vertex, 1),
                 viewer_ctrl_->At(vertex, 2));
    }
  } else {
    flag_end = true;
  }
}

void CustomGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);  // Установка области отображения
  glMatrixMode(GL_PROJECTION);  // Режим проекции
  glLoadIdentity();             // Сброс матрицы
  // Установка области видимости
  const qreal aspectRatio = qreal(width) / qreal(height ? height : 1);
  glOrtho(-1 * aspectRatio, 1 * aspectRatio, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);  // Режим моделирования
  emit ChangeFontSize();
}

void CustomGLWidget::paintEvent(QPaintEvent *event) {
  QOpenGLWidget::paintEvent(event);
  QPainter painter(this);
  painter.setPen(QColor(10, 132, 255));  // Установка синего цвета границы
  painter.drawRect(rect());
}

void CustomGLWidget::SaveImage(char type) {
  QDir screenshotsDir = src_dir;
  screenshotsDir.mkdir("screenshots");
  screenshotsDir.cd("screenshots");
  QString foldername = screenshotsDir.absolutePath() + "/";
  QImage image = this->grabFramebuffer();
  if (type == 'b') {
    QString filename = GenerateFilename(foldername, "bmp", 1);
    image.save(filename, "BMP");
  } else {
    QString filename = GenerateFilename(foldername, "jpeg", 1);
    int quality = 100;
    image.save(filename, "JPEG", quality);
  }
}

QString CustomGLWidget::GenerateFilename(const QString &dir,
                                         const QString &extension, int i) {
  QString time = QDateTime::currentDateTime().toString("yy_dd_hh_mm_ss");
  time += '_' + QString::number(i);
  QString filename = dir + "shot_" + time + "." + extension;
  return filename;
}

void CustomGLWidget::SaveAnimation() {
  QDir animationsDir = src_dir;
  animationsDir.mkdir("animations");
  animationsDir.cd("animations");
  QString foldername = animationsDir.absolutePath() + "/";
  QString inner_folder = MakeDirs(foldername);
  int FPS = 10, s = 5;
  int delay_ms = 1000 / FPS;
  int frames_N = s * FPS;
  QTimer *timer = new QTimer(this);
  timer->setInterval(delay_ms);
  timer->setSingleShot(false);
  int i = 1;
  connect(timer, &QTimer::timeout, this,
          [this, timer, inner_folder, i, frames_N, delay_ms]() mutable {
            SaveFrame(inner_folder, i);
            i++;
            if (i > frames_N) {
              timer->stop();
              timer->deleteLater();
              RecordAnimation(inner_folder, delay_ms, frames_N);
            }
          });

  timer->start();
}

QString CustomGLWidget::MakeDirs(QString foldername) {
  QDir dir(foldername);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  QString time = QDateTime::currentDateTime().toString("yy_dd_hh_mm_ss");
  QString inner_folder = foldername + time + '/';
  QDir in_dir(inner_folder);
  if (!in_dir.exists()) {
    in_dir.mkpath(".");
  }
  return inner_folder;
}

void CustomGLWidget::SaveFrame(QString path, int i) {
  QImage frame = this->grabFramebuffer();
  int width = 640, height = 480;
  if (!frame.isNull()) {
    frame = frame.scaled(width, height);
    QString filename = path + QString::number(i) + ".bmp";
    frame.save(filename, "BMP");
  }
}

void CustomGLWidget::RecordAnimation(QString path, int delay_ms, int frames_N) {
  QString gif_filename = path + "animation.gif";
  int width = 640, height = 480;
  GifWriter gif;
  GifBegin(&gif, gif_filename.toUtf8().constData(), width, height, delay_ms);
  for (int i = 1; i < frames_N + 1; i++) {
    QString frame_name = path + QString::number(i) + ".bmp";
    QImage frame_image(frame_name);
    QFile file(frame_name);
    if (!frame_image.isNull()) {
      const uint8_t *bitsPtr = frame_image.bits();
      GifWriteFrame(&gif, bitsPtr, width, height, delay_ms);
      file.remove();
    }
  }
  GifEnd(&gif);
}

}  // namespace s21
