#include "s21_matrix_oop.h"

double S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}
double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (*this == other) return *this;
  deleteMatrix();
  cols_ = other.cols_;
  rows_ = other.rows_;
  createMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res = *this;
  return res += other;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res = *this;
  return res -= other;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &value) {
  MulNumber(value);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double &value) const {
  S21Matrix res = *this;
  res.MulNumber(value);
  return res;
}

S21Matrix operator*(const double &value, const S21Matrix &matrix) {
  S21Matrix res = matrix;
  return res *= value;
}
