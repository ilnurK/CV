#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &copy) {
  if (this != &copy) {
    rows_ = copy.rows_;
    cols_ = copy.cols_;
    if (matrix_) {
      delete[] matrix_;
    }
    size_t size = rows_ * cols_;
    matrix_ = new double[size]();
    memcpy(matrix_, copy.matrix_, size * sizeof(double));
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&moved) {
  if (this != &moved) {
    delete[] matrix_;
    rows_ = moved.rows_;
    cols_ = moved.cols_;
    matrix_ = moved.matrix_;
    moved.matrix_ = nullptr;
    moved.rows_ = moved.cols_ = 0;
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) const {
  CheckBounds(row, col);
  return matrix_[ID(row, col)];
}

double &S21Matrix::operator()(int row, int col) {
  CheckBounds(row, col);
  return matrix_[ID(row, col)];
}
