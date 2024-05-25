#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

void MainWindow::MakeConnections() {
  // Подключение изменений слайдеров и spinBox
  connect(ui->spin_box_move_x, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_move_z, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_move_y, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_rotate_x, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_rotate_y, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_rotate_z, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->spin_box_scale, SIGNAL(valueChanged(double)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_move_x, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_move_y, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_move_z, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_rotate_x, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_rotate_y, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_rotate_z, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));
  connect(ui->slider_scale, SIGNAL(valueChanged(int)), this,
          SLOT(ValueChanged()));

  // Смена типа проекции
  connect(ui->projection_parallel, &QAction::triggered, this,
          &MainWindow::ProjectionTypeChanged);
  connect(ui->projection_central, &QAction::triggered, this,
          &MainWindow::ProjectionTypeChanged);

  // Подключение мыши
  connect(ui->open_gl_widget, &CustomGLWidget::wheelDeltaChanged, this,
          &MainWindow::UpdateScaleValue);
  connect(ui->open_gl_widget, &CustomGLWidget::mouseMoved, this,
          &MainWindow::UpdateRotateValue);

  // Изменение размера шрифта
  connect(ui->open_gl_widget, &CustomGLWidget::ChangeFontSize, this,
          &MainWindow::ChangeFontSize);
}

}  // namespace s21
