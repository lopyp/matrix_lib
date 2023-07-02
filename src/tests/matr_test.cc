#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_matrix_oop.h"

TEST(MatrixTests, init0) {
  S21Matrix TestMatrix;
  EXPECT_EQ(TestMatrix.getRows(), 3);
  EXPECT_EQ(TestMatrix.getCols(), 3);
  EXPECT_EQ(TestMatrix(0, 0), 0);
}

TEST(MatrixTests, init1) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(1, 1);
  TestMatrix2(0, 0) = 1;
  TestMatrix2.setCols(3);
  TestMatrix2.setRows(3);
  TestMatrix1(0, 0) = 1;
  EXPECT_TRUE(TestMatrix1 == TestMatrix2);
}

TEST(MatrixTests, init2) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(1, 1);
  TestMatrix1(0, 0) = 1;
  TestMatrix2(0, 0) = 1;
  TestMatrix1.setCols(1);
  TestMatrix1.setRows(1);
  EXPECT_TRUE(TestMatrix1 == TestMatrix2);
}

TEST(MatrixTests, init3) {
  S21Matrix TestMatrix1(4, 2);
  TestMatrix1(0, 0) = 3.14;
  TestMatrix1(0, 1) = 0.56;
  TestMatrix1(1, 0) = -69.3;
  TestMatrix1(1, 1) = 0;
  S21Matrix TestMatrix2(TestMatrix1);
  EXPECT_TRUE(TestMatrix1 == TestMatrix2);
}

TEST(MatrixTests, moveConstructor) {
  S21Matrix TestMatrix2(3, 3);
  S21Matrix TestMatrix3(3, 3);
  TestMatrix2(0, 0) = 1;
  TestMatrix3(0, 0) = 1;
  S21Matrix TestMatrix1(std::move(TestMatrix2));
  EXPECT_TRUE(TestMatrix1 == TestMatrix3);
}

TEST(MatrixTests, incorrectInit0) {
  EXPECT_THROW(S21Matrix TestMatrix(3, -1), std::out_of_range);
}

TEST(MatrixTests, incorrectInit1) {
  EXPECT_THROW(S21Matrix TestMatrix(-3, 1), std::out_of_range);
}

TEST(MatrixTests, incorrectInit2) {
  EXPECT_THROW(S21Matrix TestMatrix(0, 1), std::out_of_range);
}

TEST(MatrixTests, getRols) {
  S21Matrix TestMatrix1(4, 4);
  EXPECT_EQ(TestMatrix1.getCols(), 4);
  S21Matrix TestMatrix2;
  EXPECT_EQ(TestMatrix2.getCols(), 3);
}

TEST(MatrixTests, getRows) {
  S21Matrix TestMatrix1(4, 4);
  EXPECT_EQ(TestMatrix1.getRows(), 4);
  S21Matrix TestMatrix2;
  EXPECT_EQ(TestMatrix2.getRows(), 3);
}

TEST(MatrixTests, setCols) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1(1, 1) = 4;
  TestMatrix1.setCols(4);
  EXPECT_EQ(TestMatrix1.getCols(), 4);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
  TestMatrix1.setCols(2);
  EXPECT_EQ(TestMatrix1.getCols(), 2);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
}

TEST(MatrixTests, setRows) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1(1, 1) = 4;
  TestMatrix1.setRows(4);
  EXPECT_EQ(TestMatrix1.getRows(), 4);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
  TestMatrix1.setRows(2);
  EXPECT_EQ(TestMatrix1.getRows(), 2);
  EXPECT_EQ(TestMatrix1(1, 1), 4);
}

TEST(MatrixTests, set_cols_incorrect) {
  S21Matrix TestMatrix1(3, 3);
  EXPECT_THROW(TestMatrix1.setRows(-4), std::out_of_range);
}

TEST(MatrixTests, set_rows_incorrect) {
  S21Matrix TestMatrix1(3, 3);
  EXPECT_THROW(TestMatrix1.setCols(-4), std::out_of_range);
}

TEST(MatrixTests, EqMatrix0) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(3, 3);
  TestMatrix1(2, 2) = 1;
  EXPECT_FALSE(TestMatrix1.EqMatrix(TestMatrix2));
}

TEST(MatrixTests, EqMatrix1) {
  S21Matrix TestMatrix1(2, 3);
  S21Matrix TestMatrix2(3, 3);
  TestMatrix1(1, 2) = 1;
  EXPECT_FALSE(TestMatrix1.EqMatrix(TestMatrix2));
}

TEST(MatrixTests, EqMatrix2) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(3, 2);
  TestMatrix1(2, 2) = 1;
  EXPECT_FALSE(TestMatrix1.EqMatrix(TestMatrix2));
}

TEST(MatrixTests, EqMatrix3) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(3, 3);
  TestMatrix1(2, 2) = 1;
  TestMatrix2(2, 2) = 1;
  EXPECT_TRUE(TestMatrix1.EqMatrix(TestMatrix2));
}

TEST(MatrixTests, SumMatrix1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3.14;
  TestMatrix1(0, 1) = 0.56;
  TestMatrix1(1, 0) = -69.3;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -78.14;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -0.3;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = -75;
  ResultMatrix(0, 1) = 0.56;
  ResultMatrix(1, 0) = -69.6;
  ResultMatrix(1, 1) = 2;
  EXPECT_TRUE((TestMatrix1 + TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, DivMatrix1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3;
  TestMatrix1(0, 1) = 2;
  TestMatrix1(1, 0) = -6;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -7;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -3;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = 10;
  ResultMatrix(0, 1) = 2;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = -2;
  EXPECT_TRUE((TestMatrix1 - TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, MulMatrix1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3;
  TestMatrix1(0, 1) = 2;
  TestMatrix1(1, 0) = -6.6;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -7;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -3.5;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = -28;
  ResultMatrix(0, 1) = 4;
  ResultMatrix(1, 0) = 46.2;
  ResultMatrix(1, 1) = 0;
  EXPECT_TRUE((TestMatrix1 * TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, MulMatrixNum1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = -78.14;
  TestMatrix1(0, 1) = 0;
  TestMatrix1(1, 0) = -0.3;
  TestMatrix1(1, 1) = 2;
  ResultMatrix(0, 0) = -781.4;
  ResultMatrix(0, 1) = 0;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = 20;
  EXPECT_TRUE((TestMatrix1 * 10) == ResultMatrix);
}

TEST(MatrixTests, MulNumMatrix1) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = -78.14;
  TestMatrix1(0, 1) = 0;
  TestMatrix1(1, 0) = -0.3;
  TestMatrix1(1, 1) = 2;
  ResultMatrix(0, 0) = -781.4;
  ResultMatrix(0, 1) = 0;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = 20;
  EXPECT_TRUE((10. * TestMatrix1) == ResultMatrix);
}

TEST(MatrixTests, EqMatrix) {
  S21Matrix TestMatrix2(1, 3);
  S21Matrix TestMatrix1 = TestMatrix2;
  EXPECT_TRUE(TestMatrix1 == TestMatrix2);
}

TEST(MatrixTests, EqSumMatrix) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3.14;
  TestMatrix1(0, 1) = 0.56;
  TestMatrix1(1, 0) = -69.3;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -78.14;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -0.3;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = -75;
  ResultMatrix(0, 1) = 0.56;
  ResultMatrix(1, 0) = -69.6;
  ResultMatrix(1, 1) = 2;
  EXPECT_TRUE((TestMatrix1 += TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, EqSubMatrix) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3;
  TestMatrix1(0, 1) = 2;
  TestMatrix1(1, 0) = -6;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -7;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -3;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = 10;
  ResultMatrix(0, 1) = 2;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = -2;
  EXPECT_TRUE((TestMatrix1 -= TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, EqMulMatrixNumber) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = -78.14;
  TestMatrix1(0, 1) = 0;
  TestMatrix1(1, 0) = -0.3;
  TestMatrix1(1, 1) = 2;
  ResultMatrix(0, 0) = -781.4;
  ResultMatrix(0, 1) = 0;
  ResultMatrix(1, 0) = -3;
  ResultMatrix(1, 1) = 20;
  EXPECT_TRUE((TestMatrix1 *= 10) == ResultMatrix);
}

TEST(MatrixTests, EqMulMatrix) {
  S21Matrix TestMatrix1(2, 2);
  S21Matrix TestMatrix2(2, 2);
  S21Matrix ResultMatrix(2, 2);
  TestMatrix1(0, 0) = 3;
  TestMatrix1(0, 1) = 2;
  TestMatrix1(1, 0) = -6.6;
  TestMatrix1(1, 1) = 0;
  TestMatrix2(0, 0) = -7;
  TestMatrix2(0, 1) = 0;
  TestMatrix2(1, 0) = -3.5;
  TestMatrix2(1, 1) = 2;
  ResultMatrix(0, 0) = -28;
  ResultMatrix(0, 1) = 4;
  ResultMatrix(1, 0) = 46.2;
  ResultMatrix(1, 1) = 0;
  EXPECT_TRUE((TestMatrix1 *= TestMatrix2) == ResultMatrix);
}

TEST(MatrixTests, Transpose) {
  S21Matrix TestMatrix1(4, 3);
  S21Matrix ResultMatrix(3, 4);
  TestMatrix1(0, 0) = 7;
  TestMatrix1(0, 1) = -98;
  TestMatrix1(0, 2) = 0.5;
  TestMatrix1(1, 0) = 0;
  TestMatrix1(1, 1) = 5.4;
  TestMatrix1(1, 2) = 32;
  TestMatrix1(2, 0) = 3.12;
  TestMatrix1(2, 1) = 2323;
  TestMatrix1(2, 2) = 23;
  TestMatrix1(3, 0) = -78;
  TestMatrix1(3, 1) = 476.4;
  TestMatrix1(3, 2) = 21;
  ResultMatrix(0, 0) = 7;
  ResultMatrix(0, 1) = 0;
  ResultMatrix(0, 2) = 3.12;
  ResultMatrix(0, 3) = -78;
  ResultMatrix(1, 0) = -98;
  ResultMatrix(1, 1) = 5.4;
  ResultMatrix(1, 2) = 2323;
  ResultMatrix(1, 3) = 476.4;
  ResultMatrix(2, 0) = 0.5;
  ResultMatrix(2, 1) = 32;
  ResultMatrix(2, 2) = 23;
  ResultMatrix(2, 3) = 21;
  S21Matrix res = TestMatrix1.Transpose();
  EXPECT_TRUE(res == ResultMatrix);
}
TEST(MatrixTests, IncorrectSumMatrix) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(2, 3);
  EXPECT_THROW(TestMatrix1.SumMatrix(TestMatrix2), std::invalid_argument);
}

TEST(MatrixTests, IncorrectSubMatrix) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(2, 3);
  EXPECT_THROW(TestMatrix1.SubMatrix(TestMatrix2), std::invalid_argument);
}

TEST(MatrixTests, IncorrectMulMatrix) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(2, 3);
  EXPECT_THROW(TestMatrix1.MulMatrix(TestMatrix2), std::invalid_argument);
}

TEST(MatrixTests, IncorrectCalcComplements0) {
  S21Matrix TestMatrix1(3, 2);
  EXPECT_THROW(TestMatrix1.CalcComplements(), std::invalid_argument);
}

TEST(MatrixTests, IncorrectcDeterminant) {
  S21Matrix TestMatrix1(3, 2);
  EXPECT_THROW(TestMatrix1.Determinant(), std::invalid_argument);
}

TEST(MatrixTests, IncorrectcBrackets) {
  S21Matrix TestMatrix1(3, 2);
  EXPECT_THROW(TestMatrix1(4, 1), std::out_of_range);
}

TEST(MatrixTests, InverseMat1) {
  S21Matrix TestMatrix1(1, 1);
  S21Matrix TestMatrix2(1, 1);
  TestMatrix1(0, 0) = 1;
  TestMatrix2(0, 0) = 1;
  S21Matrix aaa = TestMatrix1.InverseMatrix();
  EXPECT_TRUE(TestMatrix1.InverseMatrix() == TestMatrix2);
}

TEST(MatrixTests, IncorrectInverseMat1) {
  S21Matrix TestMatrix1(5, 2);
  EXPECT_THROW(TestMatrix1.InverseMatrix(), std::invalid_argument);
}

TEST(MatrixTests, IncorrectConstBrackets) {
  S21Matrix const TestMatrix1(5, 2);
  EXPECT_THROW(TestMatrix1(6, 1), std::out_of_range);
}

TEST(MatrixTests, BracketsConst) {
  S21Matrix const TestMatrix1(5, 2);
  double test = TestMatrix1(1, 1);
  EXPECT_EQ(0, test);
}

TEST(MatrixTests, CalcComplements) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1(0, 0) = 1;
  TestMatrix1(0, 1) = 2;
  TestMatrix1(0, 2) = 3;
  TestMatrix1(1, 0) = 0;
  TestMatrix1(1, 1) = 4;
  TestMatrix1(1, 2) = 2;
  TestMatrix1(2, 0) = 5;
  TestMatrix1(2, 1) = 2;
  TestMatrix1(2, 2) = 1;
  S21Matrix TestMatrix2 = TestMatrix1.CalcComplements();
  S21Matrix TestMatrix3(3, 3);
  TestMatrix3(0, 0) = 0;
  TestMatrix3(0, 1) = 10;
  TestMatrix3(0, 2) = -20;
  TestMatrix3(1, 0) = 4;
  TestMatrix3(1, 1) = -14;
  TestMatrix3(1, 2) = 8;
  TestMatrix3(2, 0) = -8;
  TestMatrix3(2, 1) = -2;
  TestMatrix3(2, 2) = 4;
  EXPECT_TRUE(TestMatrix2 == TestMatrix3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
