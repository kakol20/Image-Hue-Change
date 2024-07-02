#include "../maths/Maths.hpp"
#include "OkLCh.h"

OkLCh OkLCh::sRGBtoOkLCh(const sRGB& srgb) {
  double l1 = srgb.GetR();
  double c1 = srgb.GetG();
  double h1 = srgb.GetB();

  // to Linear RGB
  //val.Pow(2.224874);
  l1 = l1 <= 0.04045 ? l1 / 12.92 : std::pow((l1 + 0.055) / 1.055, 2.4);
  c1 = c1 <= 0.04045 ? c1 / 12.92 : std::pow((c1 + 0.055) / 1.055, 2.4);
  h1 = h1 <= 0.04045 ? h1 / 12.92 : std::pow((h1 + 0.055) / 1.055, 2.4);

  // to Linear LMS
  //val = OkLab::LinearRGBtoLinearLMS * val;
  double l2 = 0.41224204990 * l1 + 0.5362616219 * c1 + 0.05142804289 * h1;
  double c2 = 0.21194297300 * l1 + 0.6807021848 * c1 + 0.10737408160 * h1;
  double h2 = 0.08835888959 * l1 + 0.2818474475 * c1 + 0.63012965340 * h1;

  // to LMS
  //val.Cbrt()
  l1 = std::cbrt(l2);
  c1 = std::cbrt(c2);
  h1 = std::cbrt(h2);

  // to OkLab
  //val = OkLab::LMStoLab * val;
  l2 = 0.2104542553 * l1 + 0.7936177850 * c1 - 0.0040720468 * h1;
  c2 = 1.9779984950 * l1 - 2.4285922050 * c1 + 0.4505937099 * h1;
  h2 = 0.0259040371 * l1 + 0.7827717662 * c1 - 0.8086757660 * h1;

  // to OkLCh
  l1 = l2;
  c1 = std::sqrt(c2 * c2 + h2 * h2);
  h1 = Maths::UnsignedMod(std::atan2(h2, c2), Maths::Tau);
  
  return OkLCh(l1, c1, h1);
}

sRGB OkLCh::OkLChtosRGB(const OkLCh& oklch) {
  double r1 = oklch.GetL();
  double g1 = oklch.GetC();
  double b1 = oklch.GetH();

  // to OkLab
  double r2 = r1;
  double g2 = g1 * std::cos(b1);
  double b2 = g1 * std::sin(b1);

  // to LMS
  r1 = 0.9999999985 * r2 + 0.39633779220 * g2 + 0.21580375810 * b2;
  g1 = 1.0000000090 * r2 - 0.10556134230 * g2 - 0.06385417477 * b2;
  b1 = 1.0000000550 * r2 - 0.08948418209 * g2 - 1.29148553800 * b2;

  // to Linear LMS
  r2 = r1 * r1 * r1;
  g2 = g1 * g1 * g1;
  b2 = b1 * b1 * b1;

  // to Linear RGB
  r1 =  4.076538816000 * r2 - 3.3070968280 * g2 + 0.2308224516 * b2;
  g1 = -1.268606251000 * r2 + 2.6097476770 * g2 - 0.3411636353 * b2;
  b1 = -0.004197563774 * r2 - 0.7035684095 * g2 + 1.7072056180 * b2;

  // to sRGB
  r2 = r1 <= 0.00313058 ? 12.92 * r1 : (Maths::NRoot(r1, 2.4) * 1.055) - 0.055;
  g2 = g1 <= 0.00313058 ? 12.92 * g1 : (Maths::NRoot(g1, 2.4) * 1.055) - 0.055;
  b2 = b1 <= 0.00313058 ? 12.92 * b1 : (Maths::NRoot(b1, 2.4) * 1.055) - 0.055;

  return sRGB(r2, g2, b2);
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

void OkLCh::Fallback(const double change) {
  m_a = std::min(std::max(m_a, 0.), 1.);
  m_b = m_a == 0. || m_a == 1. ? 0. : m_b;

  sRGB current = OkLCh::OkLChtosRGB(*this);
  while (!current.IsInside()) {
    m_b -= change;
    m_b = std::max(m_b, 0.);

    if (m_b == 0) break;
    current = OkLCh::OkLChtosRGB(*this);
  }
}

bool OkLCh::IsInsidesRGB() const {
  sRGB current = OkLCh::OkLChtosRGB(*this);
  return current.IsInside();
}
