#ifndef WIDGET_H
#define WIDGET_H

#ifdef __linux__
#include <GL/glu.h>
#else
#include <OpenGL/glu.h>
#endif

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtOpenGL>

#include "../Controller/s21_viewer_controller.h"
#include "gif.h"

namespace s21 {

typedef struct {
  int projection_type;
  int display_method;
  int type;
  double size;
  double thickness;
  QColor color_vertices;
  QColor color_edges;
  int theme;
} settings_t;

class CustomGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 private:
  ViewerController *viewer_ctrl_{};
  QPoint last_pos;

 public:
  QDir src_dir;
  QColor default_background_color{Qt::black};
  QColor background_color;
  settings_t default_settings = {0, 0, 0, 10.0, 1.0, "#FFFFFF", "#FFFFFF", 1};
  settings_t settings;

 public:
  CustomGLWidget(QWidget *parent = nullptr);

 public:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void paintEvent(QPaintEvent *event) override;

 public:
  void SetController(ViewerController *ctrl) { viewer_ctrl_ = ctrl; }

 public:
  void SaveImage(char type);
  void SaveAnimation();
  void SaveFrame(QString path, int i);
  void RecordAnimation(QString path, int delay_ms, int frames_N);
  QString GenerateFilename(const QString &dir, const QString &extension, int i);
  QString MakeDirs(QString foldername);

 private:
  void DrawModel(int mode);
  void DrawCycle(const std::vector<double> &indices, bool &flag_end,
                 size_t &start, size_t &end, const size_t surfaces);

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 signals:
  void wheelDeltaChanged(int numDegrees);
  void mouseMoved(int dx, int dy);
  void ChangeFontSize();
};

}  // namespace s21

#endif  // WIDGET_H
