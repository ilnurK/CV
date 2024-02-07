#ifndef MATRIX_CPP_H
#define MATRIX_CPP_H

#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;
  void CheckBounds(int row, int col) const;
  void CheckDimensions(int row, int col) const;
  void CheckSquare() const;
  void CheckRows(int rows) const;
  void CheckCols(int cols) const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &copy);
  S21Matrix(S21Matrix &&moved) noexcept;
  ~S21Matrix();
  size_t ID(int row, int col) const;

  void SetRows(int new_rows);
  void SetCols(int new_cols);
  int GetRows() const;
  int GetCols() const;
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant() const;
  S21Matrix InverseMatrix();

  friend void MatrixInitArray(S21Matrix &M, double *A, size_t size);
  friend void MatrixGetArray(S21Matrix &M, double *A, size_t size);
  friend void MatrixPrint(const S21Matrix &M);
  friend void RewriteMatrix(S21Matrix &New, const S21Matrix &Old, int rows,
                            int cols);
  friend double MulMatrixIndex(const S21Matrix &temp, const S21Matrix &other,
                               int row, int col);
  friend double CalcPermutationSum(const S21Matrix &M, int *p, int sign);
  friend double GetLittleMatrixDeter(const S21Matrix &orig, int a_i, int a_j);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num);
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int row, int col);
  double &operator()(int row, int col) const;
};

bool ArraysCompare(double *a, double *b, size_t size);
void NarayanasAlgoritm(int *array, int n);
int GetMaxIdxUntilRightGreater(int *array, int idx);
int GetMaxIdxUntilLeftGreaterJ(int *array, int idx, int min_idx);
void Swap(int *array, int idx_1, int idx_2);
int GetInversionParity(int *permutations, int n);
void SwapIdxNoMatchValue(int *array, int n, int idx);

#endif
