#include <Python.h>

#include <QApplication>
#include <iostream>

#include "s21_bg_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;
  try {
    w.show();
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << "incorrect highscore path\n";
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << "bad allocation\n";
  } catch (...) {
    std::cerr << "error occured\n";
  }

  return a.exec();
}
