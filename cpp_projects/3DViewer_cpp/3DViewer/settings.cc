#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"

namespace s21 {

void MainWindow::FindingPathToSRC() {
  // Находим путь до папки src
  ui->open_gl_widget->src_dir = QApplication::applicationDirPath();
  if (QSysInfo::productType() == "macos") {
    for (int i = 0; i < 4; i++) {
      ui->open_gl_widget->src_dir.cdUp();
    }
  } else {
    ui->open_gl_widget->src_dir.cdUp();
  }
}

void MainWindow::on_background_color_triggered() {
  QColorDialog color_dialog(this);
  QColor color = color_dialog.getColor();
  if (color.isValid()) {
    ui->open_gl_widget->background_color = color;
    ui->open_gl_widget->update();
    WriteSettings();
  }
}

void MainWindow::on_settings_triggered() {
  SettingsDialog settings_dialog(&ui->open_gl_widget->settings, this);
  settings_dialog.setStyleSheet(ui->centralwidget->styleSheet());
  if (settings_dialog.exec() == QDialog::Accepted) {
    WriteSettings();
  }
  ui->open_gl_widget->update();
}

void MainWindow::ReadSettings() {
  QFile file("config.ini");
  if (file.open(QIODevice::ReadOnly)) {
    QSettings file_settings("config.ini", QSettings::IniFormat);

    ui->open_gl_widget->settings.theme =
        file_settings.value("theme", 1).toInt();
    ui->open_gl_widget->background_color =
        file_settings.value("background_color", QColor(Qt::black))
            .value<QColor>();
    ui->open_gl_widget->settings.projection_type =
        file_settings.value("projection_type", 0).toInt();
    ChangeProjectionType();

    ui->open_gl_widget->settings.display_method =
        file_settings.value("vertices/display_method", 0).toInt();
    ui->open_gl_widget->settings.size =
        file_settings.value("vertices/size", 1.0).toDouble();
    ui->open_gl_widget->settings.color_vertices =
        file_settings.value("vertices/color", "#FFFFFF").toString();

    ui->open_gl_widget->settings.thickness =
        file_settings.value("edges/thickness", 1.0).toDouble();
    ui->open_gl_widget->settings.type =
        file_settings.value("edges/type", 0).toInt();
    ui->open_gl_widget->settings.color_edges =
        file_settings.value("edges/color", "#FFFFFF").toString();

    file.close();
  } else {
    ui->open_gl_widget->background_color =
        ui->open_gl_widget->default_background_color;
    ui->open_gl_widget->settings = ui->open_gl_widget->default_settings;
  }
}

void MainWindow::WriteSettings() {
  QFile file("config.ini");
  if (file.open(QIODevice::WriteOnly)) {
    QSettings file_settings("config.ini", QSettings::IniFormat);

    file_settings.setValue("theme", ui->open_gl_widget->settings.theme);
    file_settings.setValue("background_color",
                           ui->open_gl_widget->background_color.name());
    file_settings.setValue("projection_type",
                           ui->open_gl_widget->settings.projection_type);

    file_settings.setValue("vertices/display_method",
                           ui->open_gl_widget->settings.display_method);
    file_settings.setValue("vertices/size", ui->open_gl_widget->settings.size);
    file_settings.setValue("vertices/color",
                           ui->open_gl_widget->settings.color_vertices.name());

    file_settings.setValue("edges/thickness",
                           ui->open_gl_widget->settings.thickness);
    file_settings.setValue("edges/type", ui->open_gl_widget->settings.type);
    file_settings.setValue("edges/color",
                           ui->open_gl_widget->settings.color_edges.name());

    file_settings.sync();
    file.close();
  } else
    error_ = ViewerErrors::CONFIGFILE_ERR;
}

void MainWindow::ProjectionTypeChanged() {
  QObject *senderObject = sender();
  if (senderObject == ui->projection_parallel) {
    ui->open_gl_widget->settings.projection_type = 0;
  } else if (senderObject == ui->projection_central) {
    ui->open_gl_widget->settings.projection_type = 1;
  }
  ChangeProjectionType();
  WriteSettings();
  ui->open_gl_widget->update();
}

void MainWindow::ChangeProjectionType() {
  if (ui->open_gl_widget->settings.projection_type == 0) {
    ui->projection_parallel->setChecked(true);
    ui->projection_central->setChecked(false);
  } else if (ui->open_gl_widget->settings.projection_type == 1) {
    ui->projection_central->setChecked(true);
    ui->projection_parallel->setChecked(false);
  }
}

void MainWindow::on_reset_settings_triggered() {
  int theme = ui->open_gl_widget->settings.theme;
  ui->open_gl_widget->settings = ui->open_gl_widget->default_settings;
  ui->open_gl_widget->settings.theme = theme;
  ChangeProjectionType();
  ui->open_gl_widget->background_color =
      ui->open_gl_widget->default_background_color;
  WriteSettings();
  ui->open_gl_widget->update();
}

void MainWindow::SetColorTheme() {
  QColor gray(235, 235, 235);
  if (ui->open_gl_widget->settings.theme == 0) {
    // Светлая тема
    ui->theme->setText("Тёмная тема");
    ui->centralwidget->setStyleSheet(
        "color: rgb(10, 132, 255); background-color: rgb(235, 235, 235);");
    ui->open_gl_widget->default_background_color = gray;
    ui->open_gl_widget->default_settings = {0,   0,         0,         10.0,
                                            1.0, "#000000", "#000000", 1};
  } else if (ui->open_gl_widget->settings.theme == 1) {
    // Тёмная тема
    ui->theme->setText("Светлая тема");
    ui->centralwidget->setStyleSheet(
        "color: rgb(10, 132, 255); background-color: rgb(0, 0, 0);");
    ui->open_gl_widget->default_background_color = Qt::black;
    ui->open_gl_widget->default_settings = {0,   0,         0,         10.0,
                                            1.0, "#FFFFFF", "#FFFFFF", 0};
  }
  if (ui->open_gl_widget->background_color == Qt::black ||
      ui->open_gl_widget->background_color == gray) {
    ui->open_gl_widget->background_color =
        ui->open_gl_widget->default_background_color;
  }
  if (ui->open_gl_widget->settings.color_vertices == "#FFFFFF" ||
      ui->open_gl_widget->settings.color_vertices == "#000000") {
    ui->open_gl_widget->settings.color_vertices =
        ui->open_gl_widget->default_settings.color_vertices;
  }
  if (ui->open_gl_widget->settings.color_edges == "#FFFFFF" ||
      ui->open_gl_widget->settings.color_edges == "#000000") {
    ui->open_gl_widget->settings.color_edges =
        ui->open_gl_widget->default_settings.color_edges;
  }
  WriteSettings();
}

void MainWindow::on_theme_triggered() {
  if (ui->open_gl_widget->settings.theme == 0) {
    ui->open_gl_widget->settings.theme = 1;
  } else if (ui->open_gl_widget->settings.theme == 1) {
    ui->open_gl_widget->settings.theme = 0;
  }
  SetColorTheme();
}

void MainWindow::ChangeFontSize() {
  QFont labelFont = ui->status_label->font();
  int fontSize = 16;
  labelFont.setPointSize(fontSize);
  ui->status_label->setFont(labelFont);
  fontSize = labelFont.pointSize();
  while (ui->status_label->width() < ui->status_label->fontMetrics()
                                         .boundingRect(ui->status_label->text())
                                         .width() &&
         fontSize > 10) {
    fontSize--;
    labelFont.setPointSize(fontSize);
    ui->status_label->setFont(labelFont);
  }
}

}  // namespace s21
