#include "../maths/Maths.hpp"
#include "OkLCh.h"

OkLCh OkLCh::sRGBtoOkLCh(const sRGB& srgb) {
  double l1 = srgb.GetR();
  double c1 = srgb.GetG();
  double h1 = srgb.GetB();

  // to Linear RGB
  //val.Pow(2.224874);
  l1 = std::pow(l1, 2.224874);
  c1 = std::pow(c1, 2.224874);
  h1 = std::pow(h1, 2.224874);

  // to Linear LMS
  //val = OkLab::LinearRGBtoLinearLMS * val;
  double l2 = 0.412242 * l1 + 0.536262 * c1 + 0.051428 * h1;
  double c2 = 0.211943 * l1 + 0.680702 * c1 + 0.107374 * h1;
  double h2 = 0.088359 * l1 + 0.281847 * c1 + 0.630130 * h1;

  // to LMS
  //val.Cbrt()
  l1 = std::cbrt(l2);
  c1 = std::cbrt(c2);
  h1 = std::cbrt(h2);

  // to OkLab
  //val = OkLab::LMStoLab * val;
  l2 = 0.210454 * l1 + 0.793618 * c1 - 0.004072 * h1;
  c2 = 1.977998 * l1 - 2.428592 * c1 + 0.450594 * h1;
  h2 = 0.025904 * l1 + 0.782772 * c1 - 0.808676 * h1;

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
  r1 = r2 + 0.396338 * g2 + 0.215804 * b2;
  g1 = r2 - 0.105561 * g2 - 0.063854 * b2;
  b1 = r2 - 0.089484 * g2 - 1.291486 * b2;

  // to Linear LMS
  r2 = r1 * r1 * r1;
  g2 = g1 * g1 * g1;
  b2 = b1 * b1 * b1;

  // to Linear RGB
  r1 = 4.076539 * r2 - 3.307097 * g2 + 0.230822 * b2;
  g1 = -1.268606 * r2 + 2.609748 * g2 - 0.341164 * b2;
  b1 = -0.004198 * r2 - 0.703568 * g2 + 1.707206 * b2;

  // to sRGB
  r2 = Maths::NRoot(r1, 2.224874);
  g2 = Maths::NRoot(g1, 2.224874);
  b2 = Maths::NRoot(b1, 2.224874);

  return sRGB(r2, g2, b2);
}

std::string OkLCh::Debug(const bool inDegrees) const {
  if (inDegrees) {
    return std::to_string(m_a) + ' ' + std::to_string(m_b) + ' ' + std::to_string(m_c * Maths::RadToDeg) + '\n';
  }
  else {
    return std::to_string(m_a) + ' ' + std::to_string(m_b) + ' ' + std::to_string(m_c) + '\n';
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
  sRGB current = OkLCh::OkLChtosRGB(*this);
  while (!current.IsInside()) {
    m_b -= change;
    current = OkLCh::OkLChtosRGB(*this);
  }
}

bool OkLCh::IsInsidesRGB() const {
  sRGB current = OkLCh::OkLChtosRGB(*this);
  return current.IsInside();
}
