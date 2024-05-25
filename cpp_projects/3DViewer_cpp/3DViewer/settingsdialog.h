#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QColorDialog>
#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "widget.h"

namespace s21 {

class SettingsDialog : public QDialog {
  Q_OBJECT

 public:
  SettingsDialog(settings_t *settings, QWidget *parent = nullptr);

 private:
  QComboBox *display_method;
  QComboBox *type;
  QDoubleSpinBox *size;
  QDoubleSpinBox *thickness;
  QPushButton *colorVerticesButton;
  QPushButton *colorEdgesButton;

 private slots:
  void selectColor();
  void applySettings(settings_t *settings);
  void onCancelButtonClicked();
};

}  // namespace s21

#endif  // SETTINGSDIALOG_H
