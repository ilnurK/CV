# Library for working with matrices  
## Implementation of the s21_matrix_oop.h library.
### Class attributes

Matrix class has private attributes:
rows_ - integer number of matrix rows, 
cols_ - integer number of matrix columns,
matrix_ - one-dimensional double array (to access indices as in a two-dimensional array, the ID method is used -> matrix_[i][j] == matrix[ID(i, j)].

## Class methods

setters:
  SetRows() - specifies a new value for the number of rows. If the number of rows is greater than the current one, new rows are initialized with zeros, otherwise they just disappear.
  SetCols() - specifies a new value for the number of columns. If the number of columns is greater than the current one, new columns are initialized with zeros, otherwise they just disappear.
getters:
  GetRows() - get number of rows.
  GetCols() - get number of cols.
 
EqMatrix() - Comparison of matrices.
SumMatrix() - Addition of matrices.  
SubMatrix() - Subtract matrices.  
MulNumber() - Multiplying a matrix by a number.  
MulMatrix() - Multiplying two matrices.  
Transpose() - Matrix transpose.  
CalcComplements() - Matrix of algebraic complements.  
Determinant() - Matrix determinant.  
InverseMatrix() - Inverse matrix.  

Errors caused by incorrect method arguments, non-square form, mismatched matrix shapes cause corresponding exceptions

Also for convenience, the following operators are overloaded

operator+(const S21Matrix &other);  
operator-(const S21Matrix &other);  
operator*(const S21Matrix &other);  
operator*(double num);  
operator==(const S21Matrix &other) const;  
operator=(const S21Matrix &other);  
operator=(S21Matrix &&other);  
operator+=(const S21Matrix &other);  
operator-=(const S21Matrix &other);  
operator*=(const S21Matrix &other);  
operator()(int row, int col);  
operator()(int row, int col) const;  

