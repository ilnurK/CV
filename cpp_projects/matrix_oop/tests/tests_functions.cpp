#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

using namespace std;

class S21MatrixEqTest : public testing::Test {
 protected:
  S21Matrix A;
  S21Matrix B;
};

TEST_F(S21MatrixEqTest, TestEq1) { EXPECT_EQ(A.EqMatrix(B), 1); }

TEST_F(S21MatrixEqTest, TestEq2) {
  A(0, 1) = 3;
  EXPECT_EQ(A.EqMatrix(B), 0);
}

TEST_F(S21MatrixEqTest, TestEq3) {
  A(0, 1) = 3;
  EXPECT_EQ(B.EqMatrix(A), 0);
}

TEST_F(S21MatrixEqTest, TestEq4) {
  A(0, 1) = B(0, 1) = 3.4;
  EXPECT_EQ(B.EqMatrix(A), 1);
}

TEST_F(S21MatrixEqTest, TestEq5) {
  A(0, 1) = B(0, 1) = 3.4;
  EXPECT_EQ(A.EqMatrix(B), 1);
}

TEST_F(S21MatrixEqTest, TestEq6) {
  B.SetRows(2);
  EXPECT_EQ(B.EqMatrix(A), 0);
}

TEST_F(S21MatrixEqTest, TestEq7) {
  B.SetCols(2);
  EXPECT_EQ(B.EqMatrix(A), 0);
}

class S21MatrixAllFunctions1 : public testing::Test {
 protected:
  S21Matrix A;
  S21Matrix B;
  void SetUp() override {
    double array_a[9] = {9.1,   2.34, 33.10, 34.0, 59.240,
                         468.0, 2.10, 1.234, 7.77};
    MatrixInitArray(A, array_a, 9);
    double array_b[9] = {3.21, 18, -100.2, -2.1, 32.12, 0.04, -40, 99.9, 0.64};
    MatrixInitArray(B, array_b, 9);
  }
};

TEST_F(S21MatrixAllFunctions1, TestSum1) {
  A.SumMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {12.31,  20.34, -67.1,   31.9, 91.36,
                          468.04, -37.9, 101.134, 8.41};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestSum2) {
  A.SumMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {12.31,  20.34, -67.1,   31.9, 91.36,
                          468.04, -38,   101.134, 8.41};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, TestSum3) {
  A.SumMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {12.31,  20.34, -67.1,   31.9, 91.36,
                          468.04, -37.9, 101.134, 8.41};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestSum4) {
  B.SetRows(1);
  EXPECT_THROW(A.SumMatrix(B), invalid_argument);
}

TEST_F(S21MatrixAllFunctions1, TestSub1) {
  A.SubMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {5.89,   -15.66, 133.3,   36.1, 27.12,
                          467.96, 42.1,   -98.666, 7.13};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestSub2) {
  A.SubMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {5.89,   -15.67, 133.3,   36.1, 27.12,
                          467.96, 42.1,   -98.666, 7.13};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, TestMul1) {
  A.MulMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {-1299.703,  3545.6508,  -890.5424,
                          -18735.264, 49267.9888, -3104.9104,
                          -306.6504,  853.65908,  -205.39784};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestMul2) {
  A.MulMatrix(B);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {-1299.703,  3545.6508,  -890.5424,
                          -18735.264, 49267.9888, -3104.9104,
                          -306.651,   853.65908,  -205.39784};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, TestMul3) {
  S21Matrix C(2, 1);
  EXPECT_THROW(A.MulMatrix(C), invalid_argument);
}

TEST_F(S21MatrixAllFunctions1, TestMulNum1) {
  A.MulNumber(0.2341);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {2.1303100,  0.54779400, 7.7487100,
                          7.9594000,  13.868084,  109.55880,
                          0.49161000, 0.28887940, 1.8189570};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestMulNum2) {
  A.MulNumber(0.2341);
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {2.1303100,  0.54779400, 7.7487100,
                          7.9594000,  13.868084,  109.5589,
                          0.49161000, 0.28887940, 1.8189570};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, TestTranspose1) {
  A.Transpose();
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {9.1, 34., 2.1, 2.34, 59.24, 1.234, 33.1, 468., 7.77};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestTranspose2) {
  B.Transpose();
  double test[9] = {0};
  MatrixGetArray(B, test, 9);
  double true_array[9] = {3.21, -2.1, -40, 18, 32.12, 99.9, -100.2, 0.04, 0.64};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, TestTranspose3) {
  A.Transpose();
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {9.1, 34., 2.1, 2.34, 59.2, 1.234, 33.1, 468., 7.77};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, TestTranspose4) {
  B.Transpose();
  double test[9] = {0};
  MatrixGetArray(B, test, 9);
  double true_array[9] = {3.21, -2.1, -40, 18, 32.1, 99.9, -100.2, 0.04, 0.64};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 0);
}

TEST_F(S21MatrixAllFunctions1, CalcComplements1) {
  A.CalcComplements();
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {-117.21720, 718.62000,  -82.448000,
                          22.663600,  1.1970000,  -6.3154000,
                          -865.72400, -3133.4000, 459.52400};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, CalcComplements2) {
  B.CalcComplements();
  double test[9] = {0};
  MatrixGetArray(B, test, 9);
  double true_array[9] = {16.560800,  -0.25600000, 1075.0100,
                          -10021.500, -4005.9456,  -1040.6790,
                          3219.1440,  210.29160,   140.90520};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, CalcComplements3) {
  S21Matrix C;
  double c[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  MatrixInitArray(C, c, 9);
  C.CalcComplements();
  double test[9] = {0};
  MatrixGetArray(C, test, 9);
  double true_array[9] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, CalcComplements4) {
  A.SetRows(1);
  A.SetCols(1);
  A.CalcComplements();
  double test[1] = {0};
  MatrixGetArray(A, test, 1);
  EXPECT_EQ(test[0], 1);
}

TEST_F(S21MatrixAllFunctions1, CalcDeterminant1) {
  double epsilon = 1e6;
  EXPECT_NEAR(A.Determinant(), -2114.13452, epsilon);
}

TEST_F(S21MatrixAllFunctions1, CalcDeterminant2) {
  double epsilon = 1e6;
  EXPECT_NEAR(B.Determinant(), -107667.449832, epsilon);
}

TEST_F(S21MatrixAllFunctions1, CalcDeterminant3) {
  B.SetCols(1);
  EXPECT_THROW(B.Determinant(), invalid_argument);
}

TEST_F(S21MatrixAllFunctions1, InverseMatrix1) {
  A.InverseMatrix();
  double test[9] = {0};
  MatrixGetArray(A, test, 9);
  double true_array[9] = {0.0554445,  -0.01072,     0.4094933,
                          -0.3399121, -0.000566189, 1.4821195,
                          0.0389985,  0.00298723,   -0.217358};
  EXPECT_EQ(ArraysCompare(test, true_array, 9), 1);
}

TEST_F(S21MatrixAllFunctions1, InverseMatrix2) {
  S21Matrix C;
  EXPECT_THROW(C.InverseMatrix(), domain_error);
}

TEST(Printer, print) {
  S21Matrix X(1, 1);
  X(0, 0) = 1;
  MatrixPrint(X);
}