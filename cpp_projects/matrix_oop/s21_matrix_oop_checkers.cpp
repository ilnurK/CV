#include "s21_matrix_oop.h"

using namespace std;

void S21Matrix::CheckBounds(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw out_of_range("index is out of range");
  }
}

void S21Matrix::CheckDimensions(int row, int col) const {
  if (row != rows_ || col != cols_) {
    throw invalid_argument("matrices have different shape");
  }
}

void S21Matrix::CheckSquare() const {
  if (cols_ != rows_) {
    throw invalid_argument("non-square matrix");
  }
}

void S21Matrix::CheckRows(int rows) const {
  if (rows < 1) {
    throw invalid_argument("rows number must be positive");
  }
}

void S21Matrix::CheckCols(int cols) const {
  if (cols < 1) {
    throw invalid_argument("columns number must be positive");
  }
}