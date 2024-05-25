#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QSysInfo>

#include "settingsdialog.h"
#include "widget.h"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  sliders_t sliders;

 private slots:
  void findingPathToSRC();
  void makeConnections();
  void on_chooseFile_triggered();
  void on_about_triggered();
  void ResetSliders();
  void clearFocus();
  void on_exit_triggered();
  void on_ValueChanged();
  void on_backgroundColor_triggered();
  void on_settings_triggered();
  void readSettings();
  void writeSettings();
  void on_ProjectionTypeChanged();
  void changeProjectionType();
  void on_resetSettings_triggered();
  void on_action_BMP_triggered();
  void on_action_JPEG_triggered();
  void on_action10_FPS_5_triggered();
  void updateScaleValue(int numDegrees);
  void updateRotateValue(int dx, int dy);
  void setColorTheme();
  void on_theme_triggered();
  void changeFontSize();

 private:
  Ui::MainWindow *ui;

  errors_e err_e = ALL_OK;
};
#endif  // MAINWINDOW_H
