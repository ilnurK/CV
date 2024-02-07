#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

using namespace std;

TEST(Constructors, TestInit1) {
  S21Matrix A;
  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Constructors, TestInit2) {
  EXPECT_THROW(S21Matrix A(-10, 3), invalid_argument);
}

TEST(Constructors, TestInit3) {
  EXPECT_THROW(S21Matrix A(0, 3), invalid_argument);
}

TEST(Constructors, TestInit4) {
  S21Matrix A(3, 3);
  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Constructors, TestInit5) {
  S21Matrix A(1, 8);
  EXPECT_EQ(A.GetRows(), 1);
  EXPECT_EQ(A.GetCols(), 8);
}

TEST(Constructors, TestInit6) {
  S21Matrix A;
  EXPECT_THROW(A.SetRows(0), invalid_argument);
}

TEST(Constructors, TestInit7) {
  S21Matrix A;
  EXPECT_THROW(A.SetCols(0), invalid_argument);
}

TEST(Constructors, TestInit8) {
  S21Matrix A;
  A.SetCols(5);
  A.SetCols(1);
  EXPECT_EQ(A.GetCols(), 1);
}

TEST(Constructors, TestInit9) {
  S21Matrix A;
  A.SetRows(5);
  A.SetCols(1);
  EXPECT_EQ(A.GetRows(), 5);
  EXPECT_EQ(A.GetCols(), 1);
}

TEST(Constructors, TestInit10) {
  S21Matrix A(2, 2);
  double b[4] = {0.1, 32, 2, 3.45};
  MatrixInitArray(A, b, 4);
  A.SetRows(5);
  A.SetCols(1);
  EXPECT_EQ(A.GetRows(), 5);
  EXPECT_EQ(A.GetCols(), 1);
}

class S21MatrixConstructorTest : public testing::Test {
 protected:
  S21Matrix A;
  void SetUp() override {
    A.SetRows(2);
    A.SetCols(2);
    double b[4] = {0.1, 32, 2, 3.45};
    MatrixInitArray(A, b, 4);
  }
};

TEST_F(S21MatrixConstructorTest, TestPredCopy) {
  double array[4];
  MatrixGetArray(A, array, 4);
  EXPECT_TRUE(array[0] == 0.1 && array[1] == 32 && array[2] == 2 &&
              array[3] == 3.45);
}

TEST_F(S21MatrixConstructorTest, TestCopy1) {
  S21Matrix B(A);
  EXPECT_EQ(B.EqMatrix(A), 1);
}

TEST_F(S21MatrixConstructorTest, TestCopy2) {
  S21Matrix C = A;
  EXPECT_EQ(C.EqMatrix(A), 1);
}

TEST_F(S21MatrixConstructorTest, TestCopy3) {
  S21Matrix C = A;
  EXPECT_EQ(C.EqMatrix(A), 1);
}

TEST_F(S21MatrixConstructorTest, TestExpand1) {
  A.SetRows(4);
  A.SetCols(5);
  double test[20];
  MatrixGetArray(A, test, 20);
  double true_array[20] = {0.1, 32, 0, 0, 0, 2, 3.45, 0, 0, 0,
                           0,   0,  0, 0, 0, 0, 0,    0, 0, 0};
  EXPECT_EQ(ArraysCompare(test, true_array, 20), 1);
}

TEST_F(S21MatrixConstructorTest, TestReduce1) {
  A.SetCols(1);
  double test[2];
  MatrixGetArray(A, test, 2);
  double true_array[20] = {0.1, 2};
  EXPECT_EQ(ArraysCompare(test, true_array, 2), 1);
}

TEST_F(S21MatrixConstructorTest, TestMove1) {
  S21Matrix B = move(A);
  const int S = 4;
  double test[S];
  MatrixGetArray(B, test, S);
  double true_array[S] = {0.1, 32, 2, 3.45};
  EXPECT_EQ(ArraysCompare(test, true_array, S), 1);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}