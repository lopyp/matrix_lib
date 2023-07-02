#ifndef S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define S21_MATRIXPLUS_S21_MATRIX_OOP_H_

#include <stdexcept>
#include <cmath>

class S21Matrix {
 public:
  S21Matrix();                                               
  S21Matrix(int rows, int cols);                             
  S21Matrix(const S21Matrix& other);                         
  S21Matrix(S21Matrix&& other) noexcept;                              
  ~S21Matrix();                                              

  S21Matrix& operator=(const S21Matrix& other);              
  bool operator==(const S21Matrix& other) const noexcept;                   
  S21Matrix& operator+=(const S21Matrix& other);                            
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix &other);
  S21Matrix& operator*=(const double &value);
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double &value) const;
  friend S21Matrix operator*(const double &value, const S21Matrix &matrix);
  double& operator()(int row, int col);
  double operator()(int row, int col) const;
  
  int getRows() const noexcept;
  int getCols() const noexcept;
  void setRows(const int val);
  void setCols(const int val);
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other); 
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

 private:
  void createMatrix();
  void deleteMatrix();
  S21Matrix minor(int row, int col) const;
  int rows_, cols_;                                           
  double **matrix_;                                           

};

#endif  //  S21_MATRIXPLUS_S21_MATRIX_OOP_H_

