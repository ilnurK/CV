#include "s21_matrix_oop.h"

using namespace std;

S21Matrix ::S21Matrix(int rows, int cols) {
  CheckRows(rows);
  CheckCols(cols);
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double[rows_ * cols_]();
  (matrix_) ? 0 : throw bad_alloc();
}

S21Matrix ::S21Matrix() : S21Matrix(3, 3) { ; }

S21Matrix::S21Matrix(const S21Matrix &copy)
    : S21Matrix(copy.rows_, copy.cols_) {
  memcpy(matrix_, copy.matrix_, copy.rows_ * copy.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&moved) noexcept {
  rows_ = moved.rows_;
  cols_ = moved.cols_;
  matrix_ = moved.matrix_;
  moved.matrix_ = nullptr;
  moved.rows_ = moved.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
  rows_ = cols_ = 0;
}

size_t S21Matrix::ID(int row, int col) const { return col + cols_ * row; }

void S21Matrix::SetRows(int new_rows) {
  CheckRows(new_rows);
  if (new_rows != rows_) {
    S21Matrix temp(new_rows, cols_);
    if (new_rows > rows_) {
      RewriteMatrix(temp, *this, rows_, cols_);
    } else {
      RewriteMatrix(temp, *this, new_rows, cols_);
    }
    *this = temp;
  }
}

void S21Matrix::SetCols(int new_cols) {
  CheckCols(new_cols);
  if (new_cols != cols_) {
    S21Matrix temp(rows_, new_cols);
    if (new_cols > cols_) {
      RewriteMatrix(temp, *this, rows_, cols_);
    } else {
      RewriteMatrix(temp, *this, rows_, new_cols);
    }
    *this = temp;
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void RewriteMatrix(S21Matrix &New, const S21Matrix &Old, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      New.matrix_[New.ID(i, j)] = Old.matrix_[Old.ID(i, j)];
    }
  }
}