#include "sRGB.h"

sRGB& sRGB::operator/=(const sRGB& other) {
  m_a /= other.m_a;
  m_b /= other.m_b;
  m_c /= other.m_c;
  return *this;
}

sRGB sRGB::operator/(const sRGB& other) const {
  sRGB out(*this);
  out /= other;
  return out;
}

sRGB& sRGB::operator*=(const sRGB& other) {
  m_a *= other.m_a;
  m_b *= other.m_b;
  m_c *= other.m_c;
  return *this;
}

sRGB sRGB::operator*(const sRGB& other) const {
  sRGB out(*this);
  out *= other;
  return out;
}

sRGB& sRGB::operator+=(const sRGB& other) {
  m_a += other.m_a;
  m_b += other.m_b;
  m_c += other.m_c;
  return *this;
}

sRGB sRGB::operator+(const sRGB& other) const {
  sRGB out(*this);
  out += other;
  return out;
}

sRGB& sRGB::operator-=(const sRGB& other) {
  m_a -= other.m_a;
  m_b -= other.m_b;
  m_c -= other.m_c;
  return *this;
}

sRGB sRGB::operator-(const sRGB& other) const {
  sRGB out(*this);
  out -= other;
  return out;
}

sRGB& sRGB::operator*=(const double scalar) {
  m_a *= scalar;
  m_b *= scalar;
  m_c *= scalar;
  return *this;
}

sRGB sRGB::operator*(const double scalar) const {
  sRGB out(*this);
  out *= scalar;
  return out;
}
