#pragma once

#include <string>

#include "../misc/Pseudo2DArray.hpp"

class Matrix {
public:
  Matrix(const std::vector<double>& arr = { 1 }, const unsigned int cols = 1, const unsigned int rows = 1);
  Matrix(const Pseudo2DArray<double>& arr);
  Matrix(const Matrix& other);
  ~Matrix() {};

  Matrix& operator=(const Matrix& other);

  Matrix& operator*=(const Matrix& rhs);
  Matrix operator*(const Matrix& rhs) const;

  Matrix& operator*=(const double scalar);
  Matrix operator*(const double scalar) const;

  void Pow(const double p);
  void Cbrt();
  void NRoot(const double n);

  double Determinant3x3() const;
  void Transpose();
  double Determinant2x2() const;
  bool Cofactor3x3();
  bool Invert3x3();

  std::string Debug() const { return m_mat.Debug(); };

private:
  Pseudo2DArray<double> m_mat;

  unsigned int m_cols, m_rows;
};