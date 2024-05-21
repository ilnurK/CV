#include "settingsdialog.h"

#include "mainwindow.h"

SettingsDialog::SettingsDialog(settings_t *settings, QWidget *parent)
    : QDialog(parent) {
  setWindowTitle("Настройки");
  setFixedSize(450, 250);

  // надписи
  QLabel *verticesLabel = new QLabel("Вершины", this);
  QLabel *edgesLabel = new QLabel("Рёбра", this);
  QLabel *sizeLabel = new QLabel("размер:", this);
  QLabel *thicknessLabel = new QLabel("толщина:", this);
  QLabel *colorVerticesLabel = new QLabel("цвет:", this);
  QLabel *colorEdgesLabel = new QLabel("цвет:", this);
  QLabel *emptyLabel = new QLabel("", this);
  verticesLabel->setFont(QFont("", 16));
  edgesLabel->setFont(QFont("", 16));

  // вид вершин и тип ребер
  displayMethod = new QComboBox(this);
  displayMethod->addItems({"отсутствуют", "     круги", "  квадраты"});
  displayMethod->setCurrentIndex(settings->displayMethod);
  displayMethod->setStyleSheet(
      "QComboBox { border-radius: 8px; border: 2px solid rgb(10, 132, 255); "
      "padding: 0 0 0 60; }"
      "QComboBox::drop-down { width: 0px; border-left-width: 0px; }");
  type = new QComboBox(this);
  type->addItems({"сплошные", "пунктирные"});
  type->setCurrentIndex(settings->type);
  type->setStyleSheet(
      "QComboBox { border-radius: 8px; border: 2px solid rgb(10, 132, 255); "
      "padding: 0 0 0 60; }"
      "QComboBox::drop-down { width: 0px; border-left-width: 0px; }");

  // размер вершин и толщина ребер
  size = new QDoubleSpinBox(this);
  size->setFixedSize(80, 25);
  size->setMinimum(0.01);
  size->setMaximum(100);
  size->setButtonSymbols(QAbstractSpinBox::NoButtons);
  size->setFocusPolicy(Qt::ClickFocus);
  size->setValue(settings->size);
  thickness = new QDoubleSpinBox(this);
  thickness->setFixedSize(80, 25);
  thickness->setMinimum(0.01);
  thickness->setMaximum(10.0);
  thickness->setButtonSymbols(QAbstractSpinBox::NoButtons);
  thickness->setFocusPolicy(Qt::ClickFocus);
  thickness->setValue(settings->thickness);

  // Поля выбора цвета
  colorVerticesButton = new QPushButton(this);
  colorVerticesButton->setFixedSize(80, 20);
  colorVerticesButton->setStyleSheet(
      QString("background-color: %1; border: 1px solid #424242;")
          .arg(settings->colorVertices.name()));
  colorVerticesButton->setAccessibleName(settings->colorVertices.name());
  connect(colorVerticesButton, &QPushButton::clicked, this,
          &SettingsDialog::selectColor);
  colorEdgesButton = new QPushButton(this);
  colorEdgesButton->setFixedSize(80, 20);
  colorEdgesButton->setStyleSheet(
      QString("background-color: %1; border: 1px solid #424242;")
          .arg(settings->colorEdges.name()));
  colorEdgesButton->setAccessibleName(settings->colorVertices.name());
  connect(colorEdgesButton, &QPushButton::clicked, this,
          &SettingsDialog::selectColor);

  // Кнопки
  QPushButton *applyButton = new QPushButton("Применить", this);
  QPushButton *cancelButton = new QPushButton("Отмена", this);
  applyButton->setFixedSize(196, 40);
  cancelButton->setFixedSize(196, 40);
  applyButton->setStyleSheet(
      "color: rgb(255, 255, 255); background-color: rgb(10, 132, 255); "
      "border-radius: 8px; border: 2px solid rgb(10, 132, 255);");
  cancelButton->setStyleSheet(
      "border-radius: 8px; border: 2px solid rgb(10, 132, 255);");

  // Создание сетки размещения и добавление элементов в нее
  QGridLayout *layout = new QGridLayout;
  layout->setVerticalSpacing(20);
  layout->setHorizontalSpacing(30);
  layout->addWidget(verticesLabel, 0, 0, 1, 2, Qt::AlignCenter);
  layout->addWidget(edgesLabel, 0, 2, 1, 2, Qt::AlignCenter);
  layout->addWidget(displayMethod, 1, 0, 1, 2);
  layout->addWidget(type, 1, 2, 1, 2);
  layout->addWidget(sizeLabel, 2, 0, 1, 1);
  layout->addWidget(size, 2, 1, 1, 1);
  layout->addWidget(thicknessLabel, 2, 2, 1, 1);
  layout->addWidget(thickness, 2, 3, 1, 1);
  layout->addWidget(colorVerticesLabel, 3, 0, 1, 1);
  layout->addWidget(colorVerticesButton, 3, 1, 1, 1);
  layout->addWidget(colorEdgesLabel, 3, 2, 1, 1);
  layout->addWidget(colorEdgesButton, 3, 3, 1, 1);
  layout->addWidget(emptyLabel, 4, 0, 1, 4);
  layout->addWidget(cancelButton, 5, 0, 2, 2);
  layout->addWidget(applyButton, 5, 2, 2, 2);

  // Установка сетки размещения в диалоговое окно
  setLayout(layout);

  // Подключение сигналов нажатий кнопок к слотам
  connect(applyButton, &QPushButton::clicked,
          std::bind(&SettingsDialog::applySettings, this, settings));
  connect(cancelButton, &QPushButton::clicked, this,
          &SettingsDialog::onCancelButtonClicked);
}

// Функция выбора цвета
void SettingsDialog::selectColor() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QColorDialog colorDialog(this);
  QColor selectedColor = colorDialog.getColor();
  if (selectedColor.isValid()) {
    button->setStyleSheet(
        QString("background-color: %1; border: 1px solid #424242;")
            .arg(selectedColor.name()));
    button->setAccessibleName(selectedColor.name());
  }
}

void SettingsDialog::applySettings(settings_t *settings) {
  settings->displayMethod = displayMethod->currentIndex();
  settings->type = type->currentIndex();
  settings->size = size->value();
  settings->thickness = thickness->value();
  settings->colorVertices = colorVerticesButton->accessibleName();
  settings->colorEdges = colorEdgesButton->accessibleName();
  accept();
}

void SettingsDialog::onCancelButtonClicked() { this->close(); }
