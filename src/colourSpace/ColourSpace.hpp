#pragma once

#include <string>

class ColourSpace {
public:
  ColourSpace(const double a = 0., const double b = 0., const double c = 0.) {
    m_a = a;
    m_b = b;
    m_c = c;
  }
  ColourSpace(const ColourSpace& other) {
    m_a = other.m_a;
    m_b = other.m_b;
    m_c = other.m_c;
  }
  virtual ~ColourSpace() {};

  virtual ColourSpace& operator=(const ColourSpace& other) {
    if (this == &other) return *this;
    m_a = other.m_a;
    m_b = other.m_b;
    m_c = other.m_c;
    return *this;
  }

  virtual std::string Debug() const {
    return std::to_string(m_a) + ' ' + std::to_string(m_b) + ' ' + std::to_string(m_c) + '\n';
  }

  ColourSpace& operator/=(const ColourSpace& other);
  ColourSpace& operator*=(const ColourSpace& other);
  ColourSpace& operator+=(const ColourSpace& other);
  ColourSpace& operator-=(const ColourSpace& other);
  ColourSpace& operator*=(const double scalar);

protected:
  double m_a, m_b, m_c;
};

inline ColourSpace& ColourSpace::operator/=(const ColourSpace& other) {
  m_a /= other.m_a;
  m_b /= other.m_b;
  m_c /= other.m_c;
  return *this;
}

inline ColourSpace& ColourSpace::operator*=(const ColourSpace& other) {
  m_a *= other.m_a;
  m_b *= other.m_b;
  m_c *= other.m_c;
  return *this;
}

inline ColourSpace& ColourSpace::operator+=(const ColourSpace& other) {
  m_a += other.m_a;
  m_b += other.m_b;
  m_c += other.m_c;
  return *this;
}

inline ColourSpace& ColourSpace::operator-=(const ColourSpace& other) {
  m_a -= other.m_a;
  m_b -= other.m_b;
  m_c -= other.m_c;
  return *this;
}

inline ColourSpace& ColourSpace::operator*=(const double scalar) {
  m_a *= scalar;
  m_b *= scalar;
  m_c *= scalar;
  return *this;
}
