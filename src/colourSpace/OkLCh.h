#pragma once

#include "ColourSpace.hpp"
#include "sRGB.hpp"
#include <string>

class OkLCh : public ColourSpace {
public:
  OkLCh(const double l = 0., const double c = 0., const double h = 0.) : ColourSpace(l, c, h) {};
  OkLCh(const OkLCh& other) : ColourSpace(other) {};

  double GetL() const { return m_a; };
  double GetC() const { return m_b; };
  double GetH() const { return m_c; };

  void SetL(const double l) { m_a = l; };
  void SetC(const double c) { m_b = c; };
  void SetH(const double h) { m_c = h; };

  static OkLCh sRGBtoOkLCh(const sRGB& srgb);
  static sRGB OkLChtosRGB(const OkLCh& oklch);

  /// <summary>
  /// Overriden function to account for hue value
  /// </summary>
  /// <param name="inDegrees">Stored value is in radians</param>
  /// <returns></returns>
  std::string Debug(const bool inDegrees = true) const;

  OkLCh& operator/=(const OkLCh& other);
  OkLCh& operator*=(const OkLCh& other);
  OkLCh& operator+=(const OkLCh& other);
  OkLCh& operator-=(const OkLCh& other);
  OkLCh& operator*=(const double scalar);

  OkLCh operator/(const OkLCh& other) const { OkLCh out(*this); out /= other; return out; };
  OkLCh operator*(const OkLCh& other) const { OkLCh out(*this); out *= other; return out; };
  OkLCh operator+(const OkLCh& other) const { OkLCh out(*this); out += other; return out; };
  OkLCh operator-(const OkLCh& other) const { OkLCh out(*this); out -= other; return out; };
  OkLCh operator*(const double scalar) const { OkLCh out(*this); out *= scalar; return out; };

  void Fallback(const unsigned int maxIterations = 10);
  bool IsInsidesRGB() const;
};