#ifndef MATRIXH
#define MATRIXH

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUCCESS 1
#define FAILURE 0

#define MUL 2
#define EQUAL 3
#define MUL 2
#define PLUS 1
#define MIN 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum total_enum { OK, INCORRECT_MATRIX, CALC_ERROR } total_e;

/*
0 - OK
1 - Error, incorrect matrix
2 - Calculation error (mismatched matrix sizes; matrix for which calculations
cannot be performed, etc.)
*/

// primary
// existance
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// checkers
int s21_isMatrixCorrect(matrix_t *A);
int s21_isMatrixSquare(matrix_t A);
int s21_doMatricesHaveSameSize(matrix_t A, matrix_t B);
int s21_isMat1ColsEqualMat2Rows(matrix_t A, matrix_t B);
int s21_isCellEqual(double a, double b);

// compare
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// ariphmetic
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_cycleMatrix(int type, matrix_t *A, matrix_t *B, matrix_t *result);
double s21_getMulCellNum(matrix_t A, matrix_t B, int i, int j);

// get determinant
int s21_determinant(matrix_t *A, double *result);
double s21_determinantFromPermutations(matrix_t A, total_e *total);
double s21_calcDeterminantPart(matrix_t A, int *b, int sign);
void s21_algoritmNarayanas(int *a, int n);
int s21_getMaxPosRightNeighboorGreater(int *a, int idx);
int s21_getMaxPosGreater(int *a, int idx, int min_idx);
void s21_swap(int *a, int idx_1, int idx_2);
int s21_getInversionParity(int *permutations, int n);
int s21_findInArray(int *a, int n, int num);

// transform
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_getMinDeter(matrix_t *A, matrix_t temp, double *det, int a_i, int a_j);

// secondary
int s21_matrixArrayInit(matrix_t *result, double *array, int len);
void s21_printMatrix(matrix_t result);
void s21_checkUnique(int **arr, int fact, int n);
double getRandVal();

#endif