#include "s21_matrix_oop.h"

double S21Matrix::Determinant() const {
  CheckSquare();
  double determinant = 0;
  int permut_N = 1;
  int sequence[rows_];
  for (int i = 1; i < rows_ + 1; i++) {
    sequence[i - 1] = i;
    permut_N *= i;
  }
  int *permutations = new int[rows_ * permut_N];
  for (int i = 0; i < permut_N; i++) {
    if (i) {
      NarayanasAlgoritm(sequence, rows_);
    }
    for (int j = 0; j < rows_; j++) {
      permutations[ID(i, j)] = sequence[j];
    }
    int sign = GetInversionParity(permutations + i * cols_, rows_) % 2;
    determinant += CalcPermutationSum(*this, permutations + i * cols_, sign);
  }
  delete permutations;
  return determinant;
}

double CalcPermutationSum(const S21Matrix &M, int *p, int sign) {
  double determinant = 1;
  for (int i = 0; i < M.rows_; i++) {
    determinant *= M.matrix_[M.ID(i, p[i] - 1)];
  }
  if (sign) {
    determinant *= -1;
  }
  return determinant;
}

void NarayanasAlgoritm(int *array, int n) {
  int j = n - 2;
  j = GetMaxIdxUntilRightGreater(array, j);
  int algoritm_end = (j < 0) ? 1 : 0;
  if (!algoritm_end) {
    int l = n - 1;
    l = GetMaxIdxUntilLeftGreaterJ(array, l, j);
    Swap(array, l, j);
    int k = j + 1;
    l = n - 1;
    while (k < l) {
      Swap(array, l, k);
      k++, l--;
    }
  }
}

int GetMaxIdxUntilRightGreater(int *array, int idx) {
  while (idx >= 0 && array[idx] > array[idx + 1]) {
    idx--;
  }
  return idx;
}

int GetMaxIdxUntilLeftGreaterJ(int *array, int idx, int min_idx) {
  while (idx > min_idx && (array[idx] < array[min_idx])) {
    idx--;
  }
  return idx;
}

void Swap(int *array, int idx_1, int idx_2) {
  int temp = array[idx_1];
  array[idx_1] = array[idx_2];
  array[idx_2] = temp;
}

int GetInversionParity(int *permutations, int n) {
  int count = 0;
  int temp[n];
  memcpy(temp, permutations, n * sizeof(int));
  for (int idx = 0; idx < n; idx++) {
    if (idx != temp[idx] - 1) {
      SwapIdxNoMatchValue(temp, n, idx);
      count += 1;
    }
  }
  return count;
}

void SwapIdxNoMatchValue(int *array, int n, int idx) {
  int need_idx = -1, flag_find = 0;
  while (!flag_find && need_idx < n) {
    flag_find = (idx == array[++need_idx] - 1) ? 1 : 0;
  }
  Swap(array, idx, need_idx);
}
