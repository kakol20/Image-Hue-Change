#pragma once

#include "ColourSpace.hpp"
#include <cmath>

class sRGB : public ColourSpace {
public:
  sRGB(const double r = 0, const double g = 0, const double b = 0) : ColourSpace(r, g, b) {};
  sRGB(const sRGB& other) : ColourSpace(other) {};

  double GetR() const { return m_a; };
  double GetG() const { return m_b; };
  double GetB() const { return m_c; };

  uint8_t GetRUInt() const { return uint8_t(std::round(m_a * 255.)); };
  uint8_t GetGUInt() const { return uint8_t(std::round(m_b * 255.)); };
  uint8_t GetBUInt() const { return uint8_t(std::round(m_c * 255.)); };

  static double UInt8ToDouble(const uint8_t v) { return double(v) / 255.; };

  sRGB& operator/=(const sRGB& other);
  sRGB& operator*=(const sRGB& other);
  sRGB& operator+=(const sRGB& other);
  sRGB& operator-=(const sRGB& other);
  sRGB& operator*=(const double scalar);

  sRGB operator/(const sRGB& other) const { sRGB out(*this); out /= other; return out; };
  sRGB operator*(const sRGB& other) const { sRGB out(*this); out *= other; return out; };
  sRGB operator+(const sRGB& other) const { sRGB out(*this); out += other; return out; };
  sRGB operator-(const sRGB& other) const { sRGB out(*this); out -= other; return out; };
  sRGB operator*(const double scalar) const { sRGB out(*this); out *= scalar; return out; };

  void Clamp() {
    m_a = std::max(std::min(m_a, 1.), 0.);
    m_b = std::max(std::min(m_b, 1.), 0.);
    m_c = std::max(std::min(m_c, 1.), 0.);
  }

private:

};


inline sRGB& sRGB::operator/=(const sRGB& other) {
  ColourSpace lhs(other);
  ColourSpace::operator/=(lhs);
  return *this;
}

inline sRGB& sRGB::operator*=(const sRGB& other) {
  ColourSpace lhs(other);
  ColourSpace::operator*=(lhs);
  return *this;
}

inline sRGB& sRGB::operator+=(const sRGB& other) {
  ColourSpace lhs(other);
  ColourSpace::operator+=(lhs);
  return *this;
}

inline sRGB& sRGB::operator-=(const sRGB& other) {
  ColourSpace lhs(other);
  ColourSpace::operator-=(lhs);
  return *this;
}

inline sRGB& sRGB::operator*=(const double scalar) {
  ColourSpace::operator*=(scalar);
  return *this;
}
