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

  void Fallback(const double change = 0.001);
  bool IsInsidesRGB() const;
};