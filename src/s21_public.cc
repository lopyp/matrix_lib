#include <stdexcept>

#include "s21_matrix_oop.h"

int S21Matrix::getCols() const noexcept { return cols_; }

int S21Matrix::getRows() const noexcept { return rows_; }

void S21Matrix::setCols(const int val) {
  if (val <= 0)
    throw std::out_of_range("S21Matrix::setCols: invalid size of matrix");
  if (val == cols_) return;
  S21Matrix newMatr(rows_, val);
  int currentCols = val;
  if (val > cols_) {
    currentCols = cols_;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < currentCols; j++) {
      newMatr.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = newMatr;
}

void S21Matrix::setRows(const int val) {
  if (val <= 0)
    throw std::out_of_range("S21Matrix::setRows: invalid size of matrix");
  if (val == rows_) return;
  S21Matrix newMatr(val, cols_);
  int currentRows = val;
  if (val > rows_) {
    currentRows = rows_;
  }
  for (int i = 0; i < currentRows; i++) {
    for (int j = 0; j < cols_; j++) {
      newMatr.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = newMatr;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (cols_ != other.cols_ || rows_ != other.rows_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::invalid_argument(
        "S21Matrix::SumMatrix: invalid size of one of matrices");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::invalid_argument(
        "S21Matrix::SubMatrix: invalid size of one of matrices");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "S21Matrix::MulMatrix: invalid size of one of matrices");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_)
    throw std::invalid_argument(
        "S21Matrix::Determinant: invalid size of matrix");
  int i = 0;
  int j = 0;
  int k = 0;
  int iMax = 0;
  int countSwaps = 1;
  S21Matrix tmp = *this;
  for (i = 0; i < rows_; ++i) {
    iMax = i;
    for (j = i + 1; j < rows_; ++j) {
      if (fabs(tmp(j, i)) > fabs(tmp(iMax, i))) iMax = j;
      if (fabs(tmp(iMax, i) < 1e-7)) continue;
    }
    if (i != iMax) std::swap(tmp.matrix_[i], tmp.matrix_[iMax]);
    countSwaps = -countSwaps * (i != iMax ? 1 : -1);
    for (j = i + 1; j < rows_; ++j) {
      double q = -tmp(j, i) / tmp(i, i);
      for (k = rows_ - 1; k >= i; --k) {
        tmp(j, k) += q * tmp(i, k);
      }
    }
  }
  double det = countSwaps;
  for (int i = 0; det != 0 && i < cols_; i++) {
    det *= tmp(i, i);
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_)
    throw std::invalid_argument(
        "S21Matrix::Determinant: invalid size of matrix");
  int n = rows_;
  S21Matrix result(rows_, cols_);
  if (n == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix minorMat(rows_ - 1, cols_ - 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        minorMat = minor(i, j);
        int sign = ((i + j) % 2 ? -1 : 1);
        result.matrix_[i][j] = minorMat.Determinant() * sign;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant;
  S21Matrix result(*this);
  if (rows_ != cols_ || (determinant = Determinant()) == 0)
    throw std::invalid_argument(
        "S21Matrix::InverseMatrix: invalid input matrix");
  result = Transpose().CalcComplements();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = result.matrix_[i][j] / determinant;
    }
  }
  return result;
}
