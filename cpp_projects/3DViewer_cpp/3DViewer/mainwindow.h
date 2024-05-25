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
#include <QSharedPointer>
#include <QSysInfo>
#include <fstream>
#include <map>

#include "../Controller/s21_viewer_controller.h"
#include "settingsdialog.h"
#include "widget.h"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  ViewerController *viewer_ctrl_{};
  ViewerErrors error_;
  std::map<std::string, double> sliders_{};
  const int DIVIDER_{1000};

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  void FindingPathToSRC();
  void MakeConnections();
  void ResetSliders();
  void ClearFocus();
  void InitSliders();
  void ReadSettings();
  void WriteSettings();
  void ChangeProjectionType();
  void UpdateScaleValue(int degrees);
  void UpdateRotateValue(int dx, int dy);
  void SetColorTheme();
  void ChangeFontSize();

 private slots:
  void on_choose_file_triggered();
  void on_about_triggered();
  void on_exit_triggered();
  void on_background_color_triggered();
  void on_settings_triggered();
  void on_reset_settings_triggered();
  void on_action_BMP_triggered();
  void on_action_JPEG_triggered();
  void on_action10_FPS_5_triggered();
  void on_theme_triggered();
  void ValueChanged();
  void ProjectionTypeChanged();

 private:
  Ui::MainWindow *ui;
};

}  // namespace s21

#endif  // MAINWINDOW_H
