#include "s21_matrix_oop.h"
void S21Matrix::createMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::deleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix S21Matrix::minor(int row, int col) const {
  int row_skip = 0;
  S21Matrix A(cols_ - 1, rows_ - 1);
  for (int i = 0; i < rows_ - 1; i++) {
    int column_skip = 0;
    if (i == row) {
      row_skip = 1;
    }
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) {
        column_skip = 1;
      }
      A.matrix_[i][j] = matrix_[i + row_skip][j + column_skip];
    }
  }
  return A;
}
