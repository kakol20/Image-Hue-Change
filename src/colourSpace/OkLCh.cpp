#include "../maths/Maths.hpp"
#include "OkLCh.h"

OkLCh OkLCh::sRGBtoOkLCh(const sRGB& srgb) {
  double l1 = srgb.GetR();
  double c1 = srgb.GetG();
  double h1 = srgb.GetB();

  // to reduce floating point error
  if (l1 == 1. && c1 == 1. && h1 == 1.) return OkLCh(1., 0., 0.);
  if (l1 == 0. && c1 == 0. && h1 == 0.) return OkLCh(0., 0., 0.);

  if (l1 == c1 && l1 == h1) {
    // if graycale - can skip some conversions

    // to Linear RGB
    l1 = l1 <= 0.04045 ? l1 / 12.92 : std::pow((l1 + 0.055) / 1.055, 2.4);

    // to LMS - can skip "to Linear LMS" conversion
    l1 = std::cbrt(l1);

    // can skip "to OkLab" & "to OkLCh" conversions
    return OkLCh(l1, 0., 0.);
  }
  else {
    // to Linear RGB
    l1 = l1 <= 0.04045 ? l1 / 12.92 : std::pow((l1 + 0.055) / 1.055, 2.4);
    c1 = c1 <= 0.04045 ? c1 / 12.92 : std::pow((c1 + 0.055) / 1.055, 2.4);
    h1 = h1 <= 0.04045 ? h1 / 12.92 : std::pow((h1 + 0.055) / 1.055, 2.4);

    // to Linear LMS
    double l2 = 0.4122214708 * l1 + 0.5363325363 * c1 + 0.0514459929 * h1;
    double c2 = 0.2119034982 * l1 + 0.6806995451 * c1 + 0.1073969566 * h1;
    double h2 = 0.0883024619 * l1 + 0.2817188376 * c1 + 0.6299787005 * h1;

    // to LMS
    l1 = std::cbrt(l2);
    c1 = std::cbrt(c2);
    h1 = std::cbrt(h2);

    // to OkLab
    l2 = 0.2104542553 * l1 + 0.7936177850 * c1 - 0.0040720468 * h1;
    c2 = 1.9779984951 * l1 - 2.4285922050 * c1 + 0.4505937099 * h1;
    h2 = 0.0259040371 * l1 + 0.7827717662 * c1 - 0.8086757660 * h1;

    // to OkLCh
    l1 = l2;
    c1 = std::sqrt(c2 * c2 + h2 * h2);
    h1 = Maths::UnsignedMod(std::atan2(h2, c2), Maths::Tau);

    return OkLCh(l1, c1, h1);
  }
}

sRGB OkLCh::OkLChtosRGB(const OkLCh& oklch) {
  // to reduce floating point error
  if (oklch.GetL() == 1.) return sRGB(1., 1., 1.);
  if (oklch.GetL() == 0.) return sRGB(0., 0., 0.);

  if (oklch.GetC() == 0.) {
    // if graycale - can skip some conversions

    // can skip "to OkLab" converison
    double v = oklch.GetL();

    // to Linear LMS - can skip "to LMS" conversion
    v = v * v * v;

    // to sRGB - can skip "to Linear RGB" conversion
    v = v <= 0.00313058 ? 12.92 * v : (Maths::NRoot(v, 2.4) * 1.055) - 0.055;

    return sRGB(v, v, v);
  }
  else {
    double r1 = oklch.GetL();
    double g1 = oklch.GetC();
    double b1 = oklch.GetH();

    // to OkLab
    double r2 = r1;
    double g2 = g1 * std::cos(b1);
    double b2 = g1 * std::sin(b1);

    // to LMS
    r1 = r2 + 0.3963377774 * g2 + 0.2158037573 * b2;
    g1 = r2 - 0.1055613458 * g2 - 0.0638541728 * b2;
    b1 = r2 - 0.0894841775 * g2 - 1.2914855480 * b2;

    // to Linear LMS
    r2 = r1 * r1 * r1;
    g2 = g1 * g1 * g1;
    b2 = b1 * b1 * b1;

    // to Linear RGB
    r1 =  4.0767416621 * r2 - 3.3077115913 * g2 + 0.2309699292 * b2;
    g1 = -1.2684380046 * r2 + 2.6097574011 * g2 - 0.3413193965 * b2;
    b1 = -0.0041960863 * r2 - 0.7034186147 * g2 + 1.7076147010 * b2;

    // to sRGB
    r2 = r1 <= 0.00313058 ? 12.92 * r1 : (Maths::NRoot(r1, 2.4) * 1.055) - 0.055;
    g2 = g1 <= 0.00313058 ? 12.92 * g1 : (Maths::NRoot(g1, 2.4) * 1.055) - 0.055;
    b2 = b1 <= 0.00313058 ? 12.92 * b1 : (Maths::NRoot(b1, 2.4) * 1.055) - 0.055;

    return sRGB(r2, g2, b2);
  }
}

std::string OkLCh::Debug(const bool inDegrees) const {
  if (inDegrees) {
    return std::to_string(m_a) + ' ' + std::to_string(m_b) + ' ' + std::to_string(m_c * Maths::RadToDeg);
  }
  else {
    return std::to_string(m_a) + ' ' + std::to_string(m_b) + ' ' + std::to_string(m_c);
  }
}

OkLCh& OkLCh::operator/=(const OkLCh& other) {
  ColourSpace lhs(other);
  ColourSpace::operator/=(lhs);
  m_c = Maths::UnsignedMod(m_c, Maths::Tau);
  return *this;
}

OkLCh& OkLCh::operator*=(const OkLCh& other) {
  ColourSpace lhs(other);
  ColourSpace::operator*=(lhs);
  m_c = Maths::UnsignedMod(m_c, Maths::Tau);
  return *this;
}

OkLCh& OkLCh::operator+=(const OkLCh& other) {
  ColourSpace lhs(other);
  ColourSpace::operator+=(lhs);
  m_c = Maths::UnsignedMod(m_c, Maths::Tau);
  return *this;
}

OkLCh& OkLCh::operator-=(const OkLCh& other) {
  ColourSpace lhs(other);
  ColourSpace::operator-=(lhs);
  m_c = Maths::UnsignedMod(m_c, Maths::Tau);
  return *this;
}

OkLCh& OkLCh::operator*=(const double scalar) {
  ColourSpace::operator*=(scalar);
  m_c = Maths::UnsignedMod(m_c, Maths::Tau);
  return *this;
}

void OkLCh::Fallback(const unsigned int maxIterations) {
  int iter = 0;

  while (iter < maxIterations) {
    sRGB rgb = OkLCh::OkLChtosRGB(*this);
    rgb.Clamp();

    OkLCh outLCh = OkLCh::sRGBtoOkLCh(rgb);

    m_b = outLCh.GetC();
    m_c = outLCh.GetH();

    if ((*this).IsInsidesRGB()) break;

    iter++;
  }
}

bool OkLCh::IsInsidesRGB() const {
  sRGB current = OkLCh::OkLChtosRGB(*this);
  return current.IsInside();
}