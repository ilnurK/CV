#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  findingPathToSRC();
  makeConnections();
  readSettings();
  setColorTheme();
}

MainWindow::~MainWindow() {
  FreeVertices(&ui->OpenGLWidget->vertices);
  FreeIndices(&ui->OpenGLWidget->indices);
  delete ui;
}

void MainWindow::on_chooseFile_triggered() {
  QDir modelsDir = ui->OpenGLWidget->srcDir;
  modelsDir.cd("models");
  QString filePath = QFileDialog::getOpenFileName(
      nullptr, "Открыть файл", modelsDir.absolutePath(),
      "Файлы OBJ (*.obj);;Все файлы (*.*)");
  if (!filePath.isEmpty()) {
    QByteArray arr = filePath.toUtf8();
    const char *filename = arr.data();

    FILE *file;
    err_e = ALL_OK;
    vertices_t *vertices = &(ui->OpenGLWidget->vertices);
    indices_t *indices = &(ui->OpenGLWidget->indices);
    if (!TryOpenFile(filename, &file)) {
      err_e = INVALID_FILE;
    } else {
      ResetSliders();
      FreeVertices(vertices);
      FreeIndices(indices);
      GetMatrices(file, vertices, indices, &err_e);
      if (err_e == ALL_OK) {
        QString info = "Имя файла: " + QFileInfo(filePath).baseName();
        info += ".  Количество вершин: " + QString::number(vertices->rows);
        info += ".  Количество рёбер: " +
                QString::number(vertices->rows + indices->rows - 2);
        ui->status_label->setText(info);
        changeFontSize();
        ui->OpenGLWidget->update();
        clearFocus();
      }
    }
    if (err_e != ALL_OK) {
      ui->status_label->setText(ErrorHandle(err_e));
    }
  }
}

void MainWindow::on_about_triggered() {
  QMessageBox about;
  about.setIconPixmap(QPixmap(":/icon/icon.ico"));
  about.setText(
      "3DViewer\nверсия 1.0\n\nПрограмма для визуализации каркасной модели в "
      "трёхмерном пространстве\n\nАвторы: Хаматдинов Ильнур,\nФролов Михаил, "
      "Свечников Матвей");
  about.exec();
}

void MainWindow::ResetSliders() {
  ui->sliderMoveX->setValue(0);
  ui->sliderMoveY->setValue(0);
  ui->sliderMoveZ->setValue(0);
  ui->sliderRotateX->setValue(0);
  ui->sliderRotateY->setValue(0);
  ui->sliderRotateZ->setValue(0);
  ui->sliderScale->setValue(100);
}

void MainWindow::clearFocus() {
  ui->spinBoxScale->clearFocus();
  ui->spinBoxMoveX->clearFocus();
  ui->spinBoxMoveY->clearFocus();
  ui->spinBoxMoveZ->clearFocus();
  ui->spinBoxRotateX->clearFocus();
  ui->spinBoxRotateY->clearFocus();
  ui->spinBoxRotateZ->clearFocus();
}

void MainWindow::on_exit_triggered() {
  FreeVertices(&ui->OpenGLWidget->vertices);
  FreeIndices(&ui->OpenGLWidget->indices);
  qApp->quit();
}

void MainWindow::on_ValueChanged() {
  QObject *senderObject = sender();
  if (senderObject == ui->spinBoxMoveX) {
    ui->sliderMoveX->setValue(
        static_cast<int>(ui->spinBoxMoveX->value() * DIVIDER));
  } else if (senderObject == ui->spinBoxMoveY) {
    ui->sliderMoveY->setValue(
        static_cast<int>(ui->spinBoxMoveY->value() * DIVIDER));
  } else if (senderObject == ui->spinBoxMoveZ) {
    ui->sliderMoveZ->setValue(
        static_cast<int>(ui->spinBoxMoveZ->value() * DIVIDER));
  } else if (senderObject == ui->spinBoxRotateX) {
    ui->sliderRotateX->setValue(static_cast<int>(ui->spinBoxRotateX->value()));
  } else if (senderObject == ui->spinBoxRotateY) {
    ui->sliderRotateY->setValue(static_cast<int>(ui->spinBoxRotateY->value()));
  } else if (senderObject == ui->spinBoxRotateZ) {
    ui->sliderRotateZ->setValue(static_cast<int>(ui->sliderRotateZ->value()));
  } else if (senderObject == ui->spinBoxScale) {
    ui->sliderScale->setValue(static_cast<int>(ui->spinBoxScale->value()));
  } else if (senderObject == ui->sliderMoveX) {
    ui->spinBoxMoveX->setValue(static_cast<double>(ui->sliderMoveX->value()) /
                               DIVIDER);
  } else if (senderObject == ui->sliderMoveY) {
    ui->spinBoxMoveY->setValue(static_cast<double>(ui->sliderMoveY->value()) /
                               DIVIDER);
  } else if (senderObject == ui->sliderMoveZ) {
    ui->spinBoxMoveZ->setValue(static_cast<double>(ui->sliderMoveZ->value()) /
                               DIVIDER);
  } else if (senderObject == ui->sliderRotateX) {
    ui->spinBoxRotateX->setValue(
        static_cast<double>(ui->sliderRotateX->value()));
  } else if (senderObject == ui->sliderRotateY) {
    ui->spinBoxRotateY->setValue(
        static_cast<double>(ui->sliderRotateY->value()));
  } else if (senderObject == ui->sliderRotateZ) {
    ui->spinBoxRotateZ->setValue(
        static_cast<double>(ui->sliderRotateZ->value()));
  } else if (senderObject == ui->sliderScale) {
    ui->spinBoxScale->setValue(static_cast<double>(ui->sliderScale->value()));
  }

  double moveXValue = ui->spinBoxMoveX->value() - sliders.moveX;
  double moveYValue = ui->spinBoxMoveY->value() - sliders.moveY;
  double moveZValue = ui->spinBoxMoveZ->value() - sliders.moveZ;
  double rotateXValue = ui->spinBoxRotateX->value() - sliders.rotateX;
  double rotateYValue = ui->spinBoxRotateY->value() - sliders.rotateY;
  double rotateZValue = ui->spinBoxRotateZ->value() - sliders.rotateZ;
  double scaleX = ui->spinBoxScale->value() / sliders.scale;

  sliders.moveX = ui->spinBoxMoveX->value();
  sliders.moveY = ui->spinBoxMoveY->value();
  sliders.moveZ = ui->spinBoxMoveZ->value();
  sliders.rotateX = ui->spinBoxRotateX->value();
  sliders.rotateY = ui->spinBoxRotateY->value();
  sliders.rotateZ = ui->spinBoxRotateZ->value();
  sliders.scale = ui->spinBoxScale->value();

  MoveVertexes(&(ui->OpenGLWidget->vertices), moveXValue, moveYValue,
               moveZValue);
  RotateVertexesX(&(ui->OpenGLWidget->vertices), rotateXValue);
  RotateVertexesY(&(ui->OpenGLWidget->vertices), rotateYValue);
  RotateVertexesZ(&(ui->OpenGLWidget->vertices), rotateZValue);
  ScaleVertexes(&(ui->OpenGLWidget->vertices), scaleX);

  ui->OpenGLWidget->update();
}

void MainWindow::on_action_BMP_triggered() { ui->OpenGLWidget->SaveImage('b'); }

void MainWindow::on_action_JPEG_triggered() {
  ui->OpenGLWidget->SaveImage('j');
}

void MainWindow::on_action10_FPS_5_triggered() {
  QString temp = ui->status_label->text();
  QTimer *timer = new QTimer(this);
  int delay_ms = 1000, i = 1, total_delay = 3;
  timer->setInterval(delay_ms);
  timer->setSingleShot(false);

  connect(
      timer, &QTimer::timeout, this,
      [this, timer, i, total_delay, temp]() mutable {
        ui->status_label->setText(
            QString("Запись начнётся через %1 с.").arg(total_delay - i));
        changeFontSize();
        i++;
        if (i > total_delay + 1) {
          timer->stop();
          timer->deleteLater();
          ui->status_label->setText(temp);
          changeFontSize();
          ui->status_label->setStyleSheet(
              "background-color: rgb(169, 18, 0); color: rgb(255, 255, 255);");
          ui->OpenGLWidget->SaveAnimation();
        }
      });

  timer->start();

  QTimer *timer_end = new QTimer(this);
  timer_end->setInterval(delay_ms * (total_delay + 6));
  timer_end->setSingleShot(true);
  connect(timer_end, &QTimer::timeout, this, [this]() mutable {
    ui->status_label->setStyleSheet("");
    ui->OpenGLWidget->update();
  });
  timer_end->start();
}

void MainWindow::updateScaleValue(int numDegrees) {
  ui->spinBoxScale->setValue(ui->spinBoxScale->value() + numDegrees);
}

void MainWindow::updateRotateValue(int dx, int dy) {
  ui->sliderRotateX->setValue(ui->sliderRotateX->value() + dy);
  ui->sliderRotateY->setValue(ui->sliderRotateY->value() + dx);
}
