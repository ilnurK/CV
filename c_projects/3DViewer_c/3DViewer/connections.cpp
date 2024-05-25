#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::makeConnections() {
  // Подключение изменений слайдеров и spinBox
  connect(ui->spinBoxMoveX, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxMoveY, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxMoveZ, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxRotateX, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxRotateY, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxRotateZ, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->spinBoxScale, SIGNAL(valueChanged(double)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderMoveX, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderMoveY, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderMoveZ, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderRotateX, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderRotateY, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderRotateZ, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));
  connect(ui->sliderScale, SIGNAL(valueChanged(int)), this,
          SLOT(on_ValueChanged()));

  // Смена типа проекции
  connect(ui->projectionParallel, &QAction::triggered, this,
          &MainWindow::on_ProjectionTypeChanged);
  connect(ui->projectionCentral, &QAction::triggered, this,
          &MainWindow::on_ProjectionTypeChanged);

  // Подключение мыши
  connect(ui->OpenGLWidget, &MyOpenGLWidget::wheelDeltaChanged, this,
          &MainWindow::updateScaleValue);
  connect(ui->OpenGLWidget, &MyOpenGLWidget::mouseMoved, this,
          &MainWindow::updateRotateValue);

  // Изменение размера шрифта
  connect(ui->OpenGLWidget, &MyOpenGLWidget::changeFontSize, this,
          &MainWindow::changeFontSize);
}
