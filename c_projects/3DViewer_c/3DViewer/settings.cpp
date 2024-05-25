#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"

void MainWindow::findingPathToSRC() {
  // Находим путь до папки src
  ui->OpenGLWidget->srcDir = QApplication::applicationDirPath();
  if (QSysInfo::productType() == "macos") {
    for (int i = 0; i < 4; i++) {
      ui->OpenGLWidget->srcDir.cdUp();
    }
  } else {
    ui->OpenGLWidget->srcDir.cdUp();
  }
}

void MainWindow::on_backgroundColor_triggered() {
  QColorDialog colorDialog(this);
  QColor color = colorDialog.getColor();
  if (color.isValid()) {
    ui->OpenGLWidget->backgroundColor = color;
    ui->OpenGLWidget->update();
    writeSettings();
  }
}

void MainWindow::on_settings_triggered() {
  SettingsDialog settingsDialog(&ui->OpenGLWidget->settings, this);
  settingsDialog.setStyleSheet(
      QString("background-color: %1;")
          .arg(ui->OpenGLWidget->backgroundColor.name()));
  if (settingsDialog.exec() == QDialog::Accepted) {
    writeSettings();
  }
  ui->OpenGLWidget->update();
}

void MainWindow::readSettings() {
  QFile file("config.ini");
  if (file.open(QIODevice::ReadOnly)) {
    QSettings fileSettings("config.ini", QSettings::IniFormat);

    ui->OpenGLWidget->settings.theme = fileSettings.value("theme", 1).toInt();
    ui->OpenGLWidget->backgroundColor =
        fileSettings.value("backgroundColor", QColor(Qt::black))
            .value<QColor>();
    ui->OpenGLWidget->settings.projectionType =
        fileSettings.value("projectionType", 0).toInt();
    changeProjectionType();

    ui->OpenGLWidget->settings.displayMethod =
        fileSettings.value("vertices/displayMethod", 0).toInt();
    ui->OpenGLWidget->settings.size =
        fileSettings.value("vertices/size", 1.0).toDouble();
    ui->OpenGLWidget->settings.colorVertices =
        fileSettings.value("vertices/color", "#FFFFFF").toString();

    ui->OpenGLWidget->settings.thickness =
        fileSettings.value("edges/thickness", 1.0).toDouble();
    ui->OpenGLWidget->settings.type =
        fileSettings.value("edges/type", 0).toInt();
    ui->OpenGLWidget->settings.colorEdges =
        fileSettings.value("edges/color", "#FFFFFF").toString();

    file.close();
  } else {
    ui->OpenGLWidget->backgroundColor =
        ui->OpenGLWidget->defaultBackgroundColor;
    ui->OpenGLWidget->settings = ui->OpenGLWidget->defaultSettings;
  }
}

void MainWindow::writeSettings() {
  QFile file("config.ini");
  if (file.open(QIODevice::WriteOnly)) {
    QSettings fileSettings("config.ini", QSettings::IniFormat);

    fileSettings.setValue("theme", ui->OpenGLWidget->settings.theme);
    fileSettings.setValue("backgroundColor",
                          ui->OpenGLWidget->backgroundColor.name());
    fileSettings.setValue("projectionType",
                          ui->OpenGLWidget->settings.projectionType);

    fileSettings.setValue("vertices/displayMethod",
                          ui->OpenGLWidget->settings.displayMethod);
    fileSettings.setValue("vertices/size", ui->OpenGLWidget->settings.size);
    fileSettings.setValue("vertices/color",
                          ui->OpenGLWidget->settings.colorVertices.name());

    fileSettings.setValue("edges/thickness",
                          ui->OpenGLWidget->settings.thickness);
    fileSettings.setValue("edges/type", ui->OpenGLWidget->settings.type);
    fileSettings.setValue("edges/color",
                          ui->OpenGLWidget->settings.colorEdges.name());

    fileSettings.sync();
    file.close();
  } else
    err_e = CONFIGFILE_ERR;
}

void MainWindow::on_ProjectionTypeChanged() {
  QObject *senderObject = sender();
  if (senderObject == ui->projectionParallel) {
    ui->OpenGLWidget->settings.projectionType = 0;
  } else if (senderObject == ui->projectionCentral) {
    ui->OpenGLWidget->settings.projectionType = 1;
  }
  changeProjectionType();
  writeSettings();
  ui->OpenGLWidget->update();
}

void MainWindow::changeProjectionType() {
  if (ui->OpenGLWidget->settings.projectionType == 0) {
    ui->projectionParallel->setChecked(true);
    ui->projectionCentral->setChecked(false);
  } else if (ui->OpenGLWidget->settings.projectionType == 1) {
    ui->projectionCentral->setChecked(true);
    ui->projectionParallel->setChecked(false);
  }
}

void MainWindow::on_resetSettings_triggered() {
  ui->OpenGLWidget->settings = ui->OpenGLWidget->defaultSettings;
  changeProjectionType();
  ui->OpenGLWidget->backgroundColor = ui->OpenGLWidget->defaultBackgroundColor;
  writeSettings();
  ui->OpenGLWidget->update();
}

void MainWindow::setColorTheme() {
  QColor gray(235, 235, 235);
  if (ui->OpenGLWidget->settings.theme == 0) {
    // Светлая тема
    ui->theme->setText("Тёмная тема");
    ui->centralwidget->setStyleSheet(
        "color: rgb(10, 132, 255); background-color: rgb(235, 235, 235);");
    ui->OpenGLWidget->defaultBackgroundColor = gray;
    ui->OpenGLWidget->defaultSettings = {0,   0,         0,         10.0,
                                         1.0, "#000000", "#000000", 1};
  } else if (ui->OpenGLWidget->settings.theme == 1) {
    // Тёмная тема
    ui->theme->setText("Светлая тема");
    ui->centralwidget->setStyleSheet(
        "color: rgb(10, 132, 255); background-color: rgb(0, 0, 0);");
    ui->OpenGLWidget->defaultBackgroundColor = Qt::black;
    ui->OpenGLWidget->defaultSettings = {0,   0,         0,         10.0,
                                         1.0, "#FFFFFF", "#FFFFFF", 0};
  }
  if (ui->OpenGLWidget->backgroundColor == Qt::black ||
      ui->OpenGLWidget->backgroundColor == gray) {
    ui->OpenGLWidget->backgroundColor =
        ui->OpenGLWidget->defaultBackgroundColor;
  }
  if (ui->OpenGLWidget->settings.colorVertices == "#FFFFFF" ||
      ui->OpenGLWidget->settings.colorVertices == "#000000") {
    ui->OpenGLWidget->settings.colorVertices =
        ui->OpenGLWidget->defaultSettings.colorVertices;
  }
  if (ui->OpenGLWidget->settings.colorEdges == "#FFFFFF" ||
      ui->OpenGLWidget->settings.colorEdges == "#000000") {
    ui->OpenGLWidget->settings.colorEdges =
        ui->OpenGLWidget->defaultSettings.colorEdges;
  }
  writeSettings();
}

void MainWindow::on_theme_triggered() {
  if (ui->OpenGLWidget->settings.theme == 0) {
    ui->OpenGLWidget->settings.theme = 1;
  } else if (ui->OpenGLWidget->settings.theme == 1) {
    ui->OpenGLWidget->settings.theme = 0;
  }
  setColorTheme();
}

void MainWindow::changeFontSize() {
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
