#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  FindingPathToSRC();
  MakeConnections();
  ReadSettings();
  SetColorTheme();
}

MainWindow::~MainWindow() {
  delete viewer_ctrl_;
  delete ui;
}

void MainWindow::on_choose_file_triggered() {
  QDir models_dir = ui->open_gl_widget->src_dir;
  models_dir.cd("models");
  QString file_path = QFileDialog::getOpenFileName(
      nullptr, "Открыть файл", models_dir.absolutePath(),
      "Файлы OBJ (*.obj);;Все файлы (*.*)");
  if (!file_path.isEmpty()) {
    QByteArray arr = file_path.toUtf8();
    const char *filename = arr.data();
    error_ = ViewerErrors::ALL_OK;
    delete viewer_ctrl_;
    viewer_ctrl_ = new ViewerController();
    ui->open_gl_widget->SetController(viewer_ctrl_);
    std::ifstream file{};
    if (!viewer_ctrl_) {
      error_ = ViewerErrors::MEMORY_NA;
    } else if (!viewer_ctrl_->TryOpenFile(filename, file)) {
      error_ = ViewerErrors::INVALID_FILE;
    } else {
      ResetSliders();
      InitSliders();
      viewer_ctrl_->FillMatrices(file);
      error_ = viewer_ctrl_->GetError();
      if (error_ == ViewerErrors::ALL_OK) {
        size_t vertices = viewer_ctrl_->GetVerticesQuantity();
        QString info = "Имя файла: " + QFileInfo(file_path).baseName();
        info += ".  Количество вершин: " + QString::number(vertices);
        info += ".  Количество рёбер: ";
        info += QString::number(viewer_ctrl_->GetEdges());
        ui->status_label->setText(info);
        ChangeFontSize();
        ui->open_gl_widget->update();
        ClearFocus();
      }
    }
    if (error_ != ViewerErrors::ALL_OK) {
      ui->status_label->setText((viewer_ctrl_->ErrorHandle(error_)).c_str());
    }
  }
}

void MainWindow::on_about_triggered() {
  QMessageBox about;
  about.setIconPixmap(QPixmap(":viewer.ico"));
  about.setText(
      "3DViewer\nверсия 2.0\n\nПрограмма для визуализации каркасной модели в "
      "трёхмерном пространстве\n\nАвторы: Suzann Pipe, Delena "
      "Leeanna,\nKrustofski Kwaltz ");
  about.exec();
}

void MainWindow::InitSliders() {
  sliders_["move_x"] = ui->spin_box_move_x->value();
  sliders_["move_y"] = ui->spin_box_move_z->value();
  sliders_["move_z"] = ui->spin_box_move_y->value();
  sliders_["rotate_x"] = ui->spin_box_rotate_x->value();
  sliders_["rotate_y"] = ui->spin_box_rotate_y->value();
  sliders_["rotate_z"] = ui->spin_box_rotate_z->value();
  sliders_["scale"] = ui->spin_box_scale->value();
}

void MainWindow::ResetSliders() {
  ui->slider_move_x->setValue(0);
  ui->slider_move_y->setValue(0);
  ui->slider_move_z->setValue(0);
  ui->slider_rotate_x->setValue(0);
  ui->slider_rotate_y->setValue(0);
  ui->slider_rotate_z->setValue(0);
  ui->slider_scale->setValue(100);
}

void MainWindow::ClearFocus() {
  ui->spin_box_scale->clearFocus();
  ui->spin_box_move_x->clearFocus();
  ui->spin_box_move_z->clearFocus();
  ui->spin_box_move_y->clearFocus();
  ui->spin_box_rotate_x->clearFocus();
  ui->spin_box_rotate_y->clearFocus();
  ui->spin_box_rotate_z->clearFocus();
}

void MainWindow::on_exit_triggered() { qApp->quit(); }

void MainWindow::ValueChanged() {
  QObject *senderObject = sender();
  if (senderObject == ui->spin_box_move_x) {
    ui->slider_move_x->setValue(
        static_cast<int>(ui->spin_box_move_x->value() * DIVIDER_));
  } else if (senderObject == ui->spin_box_move_z) {
    ui->slider_move_y->setValue(
        static_cast<int>(ui->spin_box_move_z->value() * DIVIDER_));
  } else if (senderObject == ui->spin_box_move_y) {
    ui->slider_move_z->setValue(
        static_cast<int>(ui->spin_box_move_y->value() * DIVIDER_));
  } else if (senderObject == ui->spin_box_rotate_x) {
    ui->slider_rotate_x->setValue(
        static_cast<int>(ui->spin_box_rotate_x->value()));
  } else if (senderObject == ui->spin_box_rotate_y) {
    ui->slider_rotate_y->setValue(
        static_cast<int>(ui->spin_box_rotate_y->value()));
  } else if (senderObject == ui->spin_box_rotate_z) {
    ui->slider_rotate_z->setValue(
        static_cast<int>(ui->slider_rotate_z->value()));
  } else if (senderObject == ui->spin_box_scale) {
    ui->slider_scale->setValue(static_cast<int>(ui->spin_box_scale->value()));
  } else if (senderObject == ui->slider_move_x) {
    ui->spin_box_move_x->setValue(
        static_cast<double>(ui->slider_move_x->value()) / DIVIDER_);
  } else if (senderObject == ui->slider_move_y) {
    ui->spin_box_move_z->setValue(
        static_cast<double>(ui->slider_move_y->value()) / DIVIDER_);
  } else if (senderObject == ui->slider_move_z) {
    ui->spin_box_move_y->setValue(
        static_cast<double>(ui->slider_move_z->value()) / DIVIDER_);
  } else if (senderObject == ui->slider_rotate_x) {
    ui->spin_box_rotate_x->setValue(
        static_cast<double>(ui->slider_rotate_x->value()));
  } else if (senderObject == ui->slider_rotate_y) {
    ui->spin_box_rotate_y->setValue(
        static_cast<double>(ui->slider_rotate_y->value()));
  } else if (senderObject == ui->slider_rotate_z) {
    ui->spin_box_rotate_z->setValue(
        static_cast<double>(ui->slider_rotate_z->value()));
  } else if (senderObject == ui->slider_scale) {
    ui->spin_box_scale->setValue(
        static_cast<double>(ui->slider_scale->value()));
  }

  double move_x = ui->spin_box_move_x->value() - sliders_["move_x"];
  double move_y = ui->spin_box_move_z->value() - sliders_["move_y"];
  double move_z = ui->spin_box_move_y->value() - sliders_["move_z"];
  double rotate_x = ui->spin_box_rotate_x->value() - sliders_["rotate_x"];
  double rotate_y = ui->spin_box_rotate_y->value() - sliders_["rotate_y"];
  double rotate_z = ui->spin_box_rotate_z->value() - sliders_["rotate_z"];
  double scale = ui->spin_box_scale->value() / sliders_["scale"];

  InitSliders();

  if (viewer_ctrl_) {
    viewer_ctrl_->MoveVertexes(move_x, move_y, move_z);
    viewer_ctrl_->RotateVertexesX(rotate_x);
    viewer_ctrl_->RotateVertexesY(rotate_y);
    viewer_ctrl_->RotateVertexesZ(rotate_z);
    viewer_ctrl_->ScaleVertexes(scale);
    ui->open_gl_widget->update();
  }
}

void MainWindow::on_action_BMP_triggered() {
  ui->open_gl_widget->SaveImage('b');
}

void MainWindow::on_action_JPEG_triggered() {
  ui->open_gl_widget->SaveImage('j');
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
        ChangeFontSize();
        i++;
        if (i > total_delay + 1) {
          timer->stop();
          timer->deleteLater();
          ui->status_label->setText(temp);
          ChangeFontSize();
          ui->status_label->setStyleSheet(
              "background-color: rgb(169, 18, 0); color: rgb(255, 255, 255);");
          ui->open_gl_widget->SaveAnimation();
        }
      });

  timer->start();

  QTimer *timer_end = new QTimer(this);
  timer_end->setInterval(delay_ms * (total_delay + 6));
  timer_end->setSingleShot(true);
  connect(timer_end, &QTimer::timeout, this, [this]() mutable {
    ui->status_label->setStyleSheet("");
    ui->open_gl_widget->update();
  });
  timer_end->start();
}

void MainWindow::UpdateScaleValue(int degrees) {
  ui->spin_box_scale->setValue(ui->spin_box_scale->value() + degrees);
}

void MainWindow::UpdateRotateValue(int dx, int dy) {
  ui->slider_rotate_x->setValue(ui->slider_rotate_x->value() + dy);
  ui->slider_rotate_y->setValue(ui->slider_rotate_y->value() + dx);
}

} // namespace s21
