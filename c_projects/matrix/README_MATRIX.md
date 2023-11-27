# Library for working with matrices  
## Matrix structure in C:  

typedef struct matrix_struct {  
  double** matrix;  
  int rows;  
  int columns;  
} matrix_t;  

## Operations on matrices

All operations (except matrix comparison) must return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

s21_create_matrix - Create matrices.  
s21_remove_matrix - Clearing matrices.  
s21_eq_matrix - Comparison of matrices.  
#define SUCCESS 1
#define FAILURE 0
s21_sum_matrix - Addition of matrices.  
s21_sub_matrix - Subtract matrices.  
s21_mult_number - Multiplying a matrix by a number.  
s21_mult_matrix - Multiplying two matrices.  
s21_transpose - Matrix transpose.  
s21_calc_complements - Matrix of algebraic complements.  
s21_determinant - Matrix determinant.  
s21_inverse_matrix - Inverse matrix.  