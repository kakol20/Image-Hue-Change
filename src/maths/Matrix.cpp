#include <cmath>

#include "Matrix.h"

Matrix::Matrix(double* arr, const unsigned int cols, const unsigned int rows) {
  m_cols = cols;
  m_rows = rows;

  m_mat = Pseudo2DArray<double>(arr, m_cols, m_rows);
}

Matrix::Matrix(const Pseudo2DArray<double>& arr) {
  m_mat = arr;
  m_cols = m_mat.GetWidth();
  m_rows = m_mat.GetHeight();
}

Matrix::Matrix(const Matrix& other) {
  m_cols = other.m_cols;
  m_rows = other.m_rows;
  m_mat = other.m_mat;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) return *this;
  m_cols = other.m_cols;
  m_rows = other.m_rows;
  m_mat = other.m_mat;
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
  if (m_cols != rhs.m_rows) return *this;

  const unsigned int newCols = rhs.m_cols;
  const unsigned int newRows = m_rows;

  Pseudo2DArray<double> newMat(newCols, newRows);

  for (unsigned int i = 0; i < newCols; i++) {
    for (unsigned int j = 0; j < newRows; j++) {
      double total = 0.;
      for (unsigned int k = 0; k < rhs.m_rows; k++) {
        total += m_mat(k, j) * rhs.m_mat(i, k);
      }
      newMat(i, j) = total;
    }
  }

  m_mat = newMat;
  m_cols = newCols;
  m_rows = newRows;
  return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
  Matrix lhs(*this);
  lhs *= rhs;
  return lhs;
}

Matrix& Matrix::operator*=(const double scalar) {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) *= scalar;
    }
  }
  return *this;
}

Matrix Matrix::operator*(const double scalar) const {
  Matrix lhs(*this);
  lhs *= scalar;
  return lhs;
}

void Matrix::Pow(const double p) {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) = std::pow(m_mat(i, j), p);
    }
  }
}

void Matrix::Cbrt() {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) = std::cbrt(m_mat(i, j));
    }
  }
}

void Matrix::NRoot(const double n) {
  const double exp = 1. / n;
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      if (std::fmod(n, 1.) == 0.) {
        m_mat(i, j) = std::pow(m_mat(i, j), exp);
      }
      else {
        double absroot = std::pow(std::abs(m_mat(i, j)), exp);
        if (m_mat(i, j) < 0.) absroot *= -1.;
        m_mat(i, j) = absroot;
      }
    }
  }
}

double Matrix::Determinant3x3() const {
  if (m_cols == 3 && m_rows == 3) {
    return 
      (m_mat(0, 0) * m_mat(1, 1) * m_mat(2, 2)) +
      (m_mat(1, 0) * m_mat(2, 1) * m_mat(0, 2)) +
      (m_mat(2, 0) * m_mat(0, 1) * m_mat(1, 2)) -
      
      (m_mat(0, 0) * m_mat(2, 1) * m_mat(1, 2)) -
      (m_mat(1, 0) * m_mat(0, 1) * m_mat(2, 2)) -
      (m_mat(2, 0) * m_mat(1, 1) * m_mat(0, 2));
  }
  return 0.0;
}

void Matrix::Transpose() {
  Pseudo2DArray<double> newMat(m_rows, m_cols);

  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      newMat(j, i) = m_mat(i, j);
    }
  }

  m_mat = newMat;
  m_cols = newMat.GetWidth();
  m_rows = newMat.GetHeight();

  //return true;
}

double Matrix::Determinant2x2() const {
  if (m_cols == 2 && m_rows == 2) {
    return (m_mat(0, 0) * m_mat(1, 1)) -
      (m_mat(1, 0) * m_mat(0, 1));
  }
  return 0.0;
}

bool Matrix::Cofactor3x3() {
  if (m_cols == 3 && m_rows == 3) {
    Pseudo2DArray<double> newMat = m_mat;
    for (unsigned int i = 0; i < m_cols; i++) {
      for (unsigned int j = 0; j < m_rows; j++) {
        //newMat(j, i) = m_mat(i, j);
        const unsigned int colMax = i <= 1 ? 2 : 1;
        const unsigned int colMin = i >= 1 ? 0 : 1;

        const unsigned int rowMax = j <= 1 ? 2 : 1;
        const unsigned int rowMin = j >= 1 ? 0 : 1;

        double detArr[] = {
          m_mat(colMin, rowMin), m_mat(colMax, rowMin),
          m_mat(colMin, rowMax), m_mat(colMax, rowMax)
        };

        const Matrix detMat(detArr, 2, 2);
        newMat(i, j) = detMat.Determinant2x2() * (double)std::pow(-1, i + j + 2);
      }
    }
    m_mat = newMat;
    return true;
  }
  return false;
}

bool Matrix::Invert3x3() {
  if (m_cols == 3 && m_rows == 3) {
    Matrix adjoint(m_mat);

    if (!adjoint.Cofactor3x3()) return false;
    adjoint.Transpose();

    const double determinant = (*this).Determinant3x3();

    if (determinant == 0.) return false;

    adjoint *= (1. / determinant);
    m_mat = adjoint.m_mat;

    return true;
  }
  return false;
}
