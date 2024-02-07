#include "s21_matrix_oop.h"

using namespace std;

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool flag_eq = (rows_ == other.rows_ && cols_ == other.cols_) ? 1 : 0;
  if (flag_eq) {
    flag_eq = ArraysCompare(matrix_, other.matrix_, rows_ * cols_);
  }
  return flag_eq;
}

bool ArraysCompare(double *a, double *b, size_t size) {
  bool flag_eq = 1;
  double epsilon = 1e-6;
  for (size_t i = 0; i < size && flag_eq; i++) {
    flag_eq = (abs(a[i] - b[i]) < epsilon) ? 1 : 0;
  }
  return flag_eq;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckDimensions(other.rows_, other.cols_);
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckDimensions(other.rows_, other.cols_);
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw invalid_argument("incorrect shape");
  }
  S21Matrix temp(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[ID(i, j)] = MulMatrixIndex(temp, other, i, j);
    }
  }
}

double MulMatrixIndex(const S21Matrix &temp, const S21Matrix &other, int row,
                      int col) {
  double res = 0;
  for (int i = 0; i < temp.cols_; i++) {
    res += temp.matrix_[temp.ID(row, i)] * other.matrix_[temp.ID(i, col)];
  }
  return res;
}

S21Matrix S21Matrix::Transpose() {
  int cols_temp = cols_;
  cols_ = rows_;
  rows_ = cols_temp;
  size_t size = rows_ * cols_;
  double *temp = new double[size];
  if (!temp) {
    throw bad_alloc();
  }
  memcpy(temp, matrix_, size * sizeof(double));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[ID(i, j)] = temp[ID(j, i)];
    }
  }
  delete[] temp;
  return *this;
}

S21Matrix S21Matrix::CalcComplements() {
  CheckSquare();
  S21Matrix temp(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double det = GetLittleMatrixDeter(temp, i, j);
      matrix_[ID(i, j)] = det * ((i + j) % 2 ? -1 : 1);
    }
  }
  return *this;
}

double GetLittleMatrixDeter(const S21Matrix &orig, int a_i, int a_j) {
  double determinant = 0;
  if (orig.rows_ > 1) {
    S21Matrix little(orig.rows_ - 1, orig.cols_ - 1);
    for (int i = 0; i < little.rows_; i++) {
      for (int j = 0; j < little.cols_; j++) {
        int idx_i = (i < a_i) ? i : i + 1;
        int idx_j = (j < a_j) ? j : j + 1;
        little.matrix_[little.ID(i, j)] = orig.matrix_[orig.ID(idx_i, idx_j)];
      }
    }
    determinant = little.Determinant();
  } else {
    determinant = 1;
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  CheckSquare();
  double determinant = this->Determinant();
  if (determinant == 0) {
    throw domain_error("determinant is zero");
  }
  this->CalcComplements();
  this->Transpose();
  double inv_det = (double)1 / determinant;
  this->MulNumber(inv_det);
  return *this;
}

void MatrixInitArray(S21Matrix &M, double *A, size_t size) {
  size_t k = 0;
  bool flag_end = 0;
  for (int i = 0; i < M.rows_ && !flag_end; i++) {
    for (int j = 0; j < M.cols_ && !flag_end; j++) {
      if (k < size) {
        M.matrix_[M.ID(i, j)] = A[k++];
      } else {
        flag_end = 1;
      }
    }
  }
}

void MatrixGetArray(S21Matrix &M, double *A, size_t size) {
  size_t k = 0;
  bool flag_end = 0;
  for (int i = 0; i < M.rows_ && !flag_end; i++) {
    for (int j = 0; j < M.cols_ && !flag_end; j++) {
      if (k < size) {
        A[k++] = M.matrix_[M.ID(i, j)];
      } else {
        flag_end = 1;
      }
    }
  }
}

void MatrixPrint(const S21Matrix &M) {
  cout << "\n";
  for (int i = 0; i < M.rows_; i++) {
    for (int j = 0; j < M.cols_; j++) {
      cout.width(10);
      cout << M.matrix_[M.ID(i, j)] << " ";
    }
    cout << "\n";
  }
}