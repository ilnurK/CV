#ifndef WIDGET_H
#define WIDGET_H

#ifdef __linux__
// #include <GL/glu.h>
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

#include "gif.h"

extern "C" {
#include "../backend/s21_3DViewer.h"
}

typedef struct {
  int projectionType;
  int displayMethod;
  int type;
  double size;
  double thickness;
  QColor colorVertices;
  QColor colorEdges;
  int theme;
} settings_t;

void DrawModel(vertices_t V, indices_t I, int mode);
QString GenerateFilename(const QString &dir, const QString &extension, int i);
QString MakeDirs(QString foldername);
void RecordAnimation(QString path, int delay_ms, int frames_N);

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  QDir srcDir;
  vertices_t vertices = {};
  indices_t indices = {};
  QColor defaultBackgroundColor = Qt::black;
  QColor backgroundColor;
  settings_t defaultSettings = {0, 0, 0, 10.0, 1.0, "#FFFFFF", "#FFFFFF", 1};
  settings_t settings;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void paintEvent(QPaintEvent *event) override;
  void SaveImage(char type);
  void SaveAnimation();
  void SaveFrame(QString path, int i);

 protected:
  QPoint lastPos;

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 signals:
  void wheelDeltaChanged(int numDegrees);
  void mouseMoved(int dx, int dy);
  void changeFontSize();
};

#endif  // WIDGET_H
