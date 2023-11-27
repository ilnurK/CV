#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  total_e total = (result != NULL)
                      ? (rows > 0 && columns > 0) ? OK : INCORRECT_MATRIX
                      : INCORRECT_MATRIX;

  if (total == OK) {
    result->matrix = NULL;
    result->rows = rows, result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *) +
                                       sizeof(double) * rows * columns);

    total = (result->matrix) ? OK : INCORRECT_MATRIX;
    double *first_cell = (!total) ? (double *)(result->matrix + rows) : NULL;

    for (int i = 0; total == OK && i < rows; i++) {
      result->matrix[i] = first_cell + i * columns;
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  }
  return total;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    free(A->matrix);
  }
  A->matrix = NULL;
  A->columns = 0, A->rows = 0;
}

int s21_isMatrixCorrect(matrix_t *A) {
  int result = 0;
  if (A != NULL) {
    result = A->rows > 0 && A->columns > 0 && A->matrix != NULL;
  }
  return result;
}

int s21_isMatrixSquare(matrix_t A) { return A.rows == A.columns; }

int s21_doMatricesHaveSameSize(matrix_t A, matrix_t B) {
  return (A.rows == B.rows) && (A.columns == B.columns);
}

int s21_isMat1ColsEqualMat2Rows(matrix_t A, matrix_t B) {
  return A.columns == B.rows;
}

int s21_isCellEqual(double a, double b) {
  total_e total = OK;
  double accur = 1e-7;
  double dif = (a > b) ? a - b : b - a;
  if (dif >= accur) {
    total = CALC_ERROR;
  } else if (round(a / accur) != round(b / accur)) {
    total = CALC_ERROR;
  }
  return total;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  matrix_t null = {0};
  total_e total = s21_cycleMatrix(EQUAL, A, B, &null);
  total = (total == OK) ? SUCCESS : FAILURE;
  s21_remove_matrix(&null);
  return total;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_cycleMatrix(PLUS, A, B, result);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_cycleMatrix(MIN, A, B, result);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  total_e total = s21_isMatrixCorrect(A) ? OK : INCORRECT_MATRIX;
  if (total == OK) {
    total = s21_create_matrix(A->rows, A->columns, result);
  }
  for (int i = 0; total == OK && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
    }
  }
  return total;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_cycleMatrix(MUL, A, B, result);
}

int s21_cycleMatrix(int type, matrix_t *A, matrix_t *B, matrix_t *result) {
  total_e total = (s21_isMatrixCorrect(A) && s21_isMatrixCorrect(B))
                      ? OK
                      : INCORRECT_MATRIX;

  int j_limit = (total == OK) ? A->columns : 0;
  if (total == OK) {
    if (type == MUL) {
      j_limit = B->columns;
      total = s21_create_matrix(A->rows, B->columns, result);
    } else if (type != EQUAL) {
      total = s21_create_matrix(A->rows, A->columns, result);
    }
  }

  if (total == OK) {
    int check = 0;
    if (type == PLUS || type == MIN || type == EQUAL) {
      check = s21_doMatricesHaveSameSize(*A, *B);
    } else if (type == MUL) {
      check = s21_isMat1ColsEqualMat2Rows(*A, *B);
    }
    total = (!check) ? CALC_ERROR : total;
  }

  for (int i = 0; total == OK && i < A->rows; i++) {
    for (int j = 0; total == OK && j < j_limit; j++) {
      if (type == MUL) {
        result->matrix[i][j] = s21_getMulCellNum(*A, *B, i, j);
      } else if (type == PLUS) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      } else if (type == MIN) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      } else if (type == EQUAL) {
        total = s21_isCellEqual(A->matrix[i][j], B->matrix[i][j]);
      }
    }
  }
  return total;
}

double s21_getMulCellNum(matrix_t A, matrix_t B, int i, int j) {
  double result = 0;
  for (int k = 0; k < A.columns; k++) {
    result += A.matrix[i][k] * B.matrix[k][j];
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  total_e total = s21_isMatrixCorrect(A) ? OK : INCORRECT_MATRIX;
  if (total == OK) {
    total = s21_isMatrixSquare(*A) ? total : CALC_ERROR;
  }
  *result = (!total) ? s21_determinantFromPermutations(*A, &total) : 0;
  return total;
}

double s21_determinantFromPermutations(matrix_t A, total_e *total) {
  double determinant = 0;
  int permut_quant = 1, n = A.rows;
  int sequence[n];
  for (int i = 1; i < n + 1; i++) {
    sequence[i - 1] = i;
    permut_quant *= i;
  }

  int **permutations = (int **)malloc(permut_quant * sizeof(int *) +
                                      n * permut_quant * sizeof(int));
  *total = (permutations == NULL) ? INCORRECT_MATRIX : *total;
  int *first_cell = (int *)(permutations + permut_quant);
  for (int i = 0; *total == OK && i < permut_quant; i++) {
    permutations[i] = first_cell + i * n;
    (i) ? s21_algoritmNarayanas(sequence, n) : 0;
    for (int j = 0; j < n; j++) {
      permutations[i][j] = sequence[j];
    }
    int sign = s21_getInversionParity(permutations[i], n) % 2;
    determinant += s21_calcDeterminantPart(A, permutations[i], sign);
  }
  free(permutations);
  return determinant;
}

double s21_calcDeterminantPart(matrix_t A, int *b, int sign) {
  double determinant = 1;
  for (int i = 0; i < A.rows; i++) {
    determinant *= A.matrix[i][b[i] - 1];
  }
  if (sign) {
    determinant *= -1;
  }
  return determinant;
}

void s21_algoritmNarayanas(int *a, int n) {
  int j = n - 2;
  j = s21_getMaxPosRightNeighboorGreater(a, j);
  int algoritm_end = (j < 0) ? 1 : 0;
  if (!algoritm_end) {
    int l = n - 1;
    l = s21_getMaxPosGreater(a, l, j);
    s21_swap(a, l, j);
    int k = j + 1;
    l = n - 1;
    while (k < l) {
      s21_swap(a, l, k);
      k++, l--;
    }
  }
}

int s21_getMaxPosRightNeighboorGreater(int *a, int idx) {
  while (idx >= 0 && a[idx] > a[idx + 1]) {
    idx--;
  }
  return idx;
}

int s21_getMaxPosGreater(int *a, int idx, int min_idx) {
  while (idx > min_idx && (a[idx] < a[min_idx])) {
    idx--;
  }
  return idx;
}

void s21_swap(int *a, int idx_1, int idx_2) {
  int temp = a[idx_1];
  a[idx_1] = a[idx_2];
  a[idx_2] = temp;
}

int s21_getInversionParity(int *permutations, int n) {
  int count = 0;
  int temp[n];
  memcpy(temp, permutations, n * sizeof(int));
  for (int i = 0; i < n; i++) {
    if (temp[i] != i + 1) {
      int need_idx = s21_findInArray(temp, n, i + 1);
      s21_swap(temp, i, need_idx);
      count++;
    }
  }
  return count;
}

int s21_findInArray(int *a, int n, int num) {
  int i = -1, flag_find = 0;
  while (!flag_find && i < n) {
    flag_find = (a[++i] == num) ? 1 : 0;
  }
  return i;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  total_e total = s21_isMatrixCorrect(A) ? OK : INCORRECT_MATRIX;
  int rows = 0, columns = 0;
  if (total == OK) {
    rows = A->columns, columns = A->rows;
    total = s21_create_matrix(rows, columns, result);
  }
  for (int i = 0; total == OK && i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return total;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  total_e total = s21_isMatrixCorrect(A) ? OK : INCORRECT_MATRIX;
  if (total == OK) {
    total = (s21_isMatrixSquare(*A)) ? total : CALC_ERROR;
  }
  double determinant = 0, flag_det_calculate = 0;
  if (total == OK) {
    total = s21_determinant(A, &determinant);
    flag_det_calculate = 1;
  }
  if (determinant && total == OK) {
    matrix_t complements = {0}, transposed = {0};
    int out = OK;
    out = (out == OK) ? s21_calc_complements(A, &complements) : out;
    out = (out == OK) ? s21_transpose(&complements, &transposed) : out;
    s21_remove_matrix(&complements);
    double inv_det = (double)1 / determinant;
    out = (out == OK) ? s21_mult_number(&transposed, inv_det, result) : out;
    s21_remove_matrix(&transposed);
    total = out;
  } else if (!determinant && flag_det_calculate) {
    total = CALC_ERROR;
  }
  return total;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  total_e total = s21_isMatrixCorrect(A) ? OK : INCORRECT_MATRIX;
  if (total == OK) {
    total = s21_isMatrixSquare(*A) ? total : CALC_ERROR;
  }
  if (total == OK) {
    total = s21_create_matrix(A->rows, A->columns, result);
  }
  matrix_t temp = {0};
  for (int i = 0; total == OK && i < result->rows; i++) {
    for (int j = 0; total == OK && j < result->columns; j++) {
      double det = 0;
      total = s21_getMinDeter(A, temp, &det, i, j);
      if (total == OK) {
        result->matrix[i][j] = det;
        result->matrix[i][j] *= (i + j) % 2 ? -1 : 1;
      }
    }
  }
  s21_remove_matrix(&temp);
  return total;
}

int s21_getMinDeter(matrix_t *A, matrix_t temp, double *det, int a_i, int a_j) {
  int rows = A->rows - 1, columns = A->columns - 1;
  total_e total = OK;
  if (rows + columns) {
    total = s21_create_matrix(rows, columns, &temp);
    for (int i = 0; total == OK && i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        int idx_i = (i < a_i) ? i : i + 1;
        int idx_j = (j < a_j) ? j : j + 1;
        temp.matrix[i][j] = A->matrix[idx_i][idx_j];
      }
    }
    total = (total == OK) ? s21_determinant(&temp, det) : 0;
  } else {
    *det = 1;
  }
  return total;
}

int s21_matrixArrayInit(matrix_t *result, double *array, int len) {
  total_e total = OK;
  int idx = 0;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns && total == OK; j++) {
      if (idx < len) {
        result->matrix[i][j] = array[idx++];
      } else {
        total = INCORRECT_MATRIX;
      }
    }
  }
  return total;
}

void s21_printMatrix(matrix_t result) {
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      printf("%25.10lf", result.matrix[i][j]);
    }
    putchar('\n');
  }
}

void s21_checkUnique(int **arr, int fact, int n) {
  int res = 1;
  for (int k = 0; k < fact && res; k++) {
    for (int i = k + 1; i < fact && res; i++) {
      int j = 0;
      while (j < n && arr[k][j] == arr[i][j]) {
        j++;
      }
      res = (j == n) ? 0 : res;
    }
  }
  (!res) ? printf("error\n") : printf("checked\n");
}

double getRandVal() {
  double num = rand() % 10;
  double denom = rand() % 100;
  return num / denom;
}