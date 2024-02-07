#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

using namespace std;

class S21MatrixOperatorParenthsTest1 : public testing::Test {
 protected:
  S21Matrix A;
};

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths1) { EXPECT_EQ(A(2, 0), 0); }

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths2) {
  A(2, 0) = 3.12;
  EXPECT_EQ(A(2, 0), 3.12);
}

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths3) { EXPECT_EQ(A(2, 0), 0); }

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths4) {
  EXPECT_THROW(A(-1, 0), out_of_range);
}

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths5) {
  EXPECT_THROW(A(2, -1), out_of_range);
}

TEST_F(S21MatrixOperatorParenthsTest1, TestParenths6) {
  EXPECT_THROW(A(3, 1), out_of_range);
}

TEST(S21MatrixOperatorParenthsTest2, TestParenths7) {
  const S21Matrix A;
  double res = A(1, 1);
  EXPECT_EQ(res, 0);
}

class S21MatrixAllOperators1 : public testing::Test {
 protected:
  S21Matrix A;
  S21Matrix B;
  const int N = 6;
  void SetUp() override {
    A.SetRows(2);
    A.SetCols(3);
    B = A;
    double array_a[N] = {30.3, -56, 0.43, 0.75, -239, 11.54};
    MatrixInitArray(A, array_a, N);
    double array_b[6] = {0.5141, 0.435, -2.1234, 1.1234, 5.0874, -0.0049};
    MatrixInitArray(B, array_b, N);
  }
};

TEST_F(S21MatrixAllOperators1, TestSumOperator1) {
  S21Matrix C = A + B;
  double test[N] = {0};
  MatrixGetArray(C, test, N);
  double true_array[N] = {30.8141, -55.565,   -1.6934,
                          1.8734,  -233.9126, 11.5351};
  EXPECT_EQ(ArraysCompare(test, true_array, N), 1);
  EXPECT_EQ(C.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestSumOperator2) {
  A += B;
  double test[N] = {0};
  MatrixGetArray(A, test, N);
  double true_array[N] = {30.8141, -55.565,   -1.6934,
                          1.8734,  -233.9126, 11.5351};
  EXPECT_EQ(ArraysCompare(test, true_array, N), 1);
  EXPECT_EQ(A.EqMatrix(B), 0);
}

TEST_F(S21MatrixAllOperators1, TestSubOperator1) {
  A -= B;
  double test[N] = {0};
  MatrixGetArray(A, test, N);
  double true_array[N] = {29.7859, -56.435,   2.55340,
                          -0.3734, -244.0874, 11.5449};
  EXPECT_EQ(ArraysCompare(test, true_array, N), 1);
  EXPECT_EQ(A.EqMatrix(B), 0);
}

TEST_F(S21MatrixAllOperators1, TestSubOperator2) {
  S21Matrix C = A - B;
  double test[N] = {0};
  MatrixGetArray(C, test, N);
  double true_array[N] = {29.7859, -56.435,   2.55340,
                          -0.3734, -244.0874, 11.5449};
  EXPECT_EQ(ArraysCompare(test, true_array, N), 1);
  EXPECT_EQ(C.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestMulOperator1) {
  B.SetRows(A.GetCols());
  S21Matrix C = A * B;
  const int S = 6;
  double test[S] = {0};
  MatrixGetArray(C, test, S);
  double true_array[N] = {-47.33317,   -271.7139,   -64.06462,
                          -268.107025, -1215.56235, -0.4214500};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
  EXPECT_EQ(C.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestMulOperator2) {
  A.SetRows(B.GetCols());
  S21Matrix C = B * A;
  const int S = 6;
  double test[S] = {0};
  MatrixGetArray(C, test, S);
  double true_array[N] = {15.9034800, -132.754600, 5.24096300,
                          37.8545700, -1278.79900, 59.1916580};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
  EXPECT_EQ(C.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestMulOperator3) {
  B.SetRows(A.GetCols());
  A *= B;
  const int S = 6;
  double test[S] = {0};
  MatrixGetArray(A, test, S);
  double true_array[N] = {-47.33317,   -271.7139,   -64.06462,
                          -268.107025, -1215.56235, -0.4214500};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
  EXPECT_EQ(B.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestMulOperator4) {
  A.SetRows(B.GetCols());
  B *= A;
  const int S = 6;
  double test[S] = {0};
  MatrixGetArray(B, test, S);
  double true_array[N] = {15.9034800, -132.754600, 5.24096300,
                          37.8545700, -1278.79900, 59.1916580};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
  EXPECT_EQ(B.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestMulNumOperator1) {
  int num = 8;
  S21Matrix C = A * num;
  const int S = 6;
  double test[S] = {0};
  MatrixGetArray(C, test, S);
  double true_array[N] = {242.4, -448.0, 3.440, 6.000, -1912., 92.32};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
  EXPECT_EQ(C.EqMatrix(A), 0);
}

TEST_F(S21MatrixAllOperators1, TestEqOperator1) {
  B = A;
  bool res = B == A;
  EXPECT_EQ(res, 1);
}

TEST_F(S21MatrixAllOperators1, TestEqMoveOperator1) {
  S21Matrix C(A);
  B = move(C);
  bool res1 = B == A;
  bool res2 = A == C;
  EXPECT_EQ(res1, 1);
  EXPECT_EQ(res2, 0);
}