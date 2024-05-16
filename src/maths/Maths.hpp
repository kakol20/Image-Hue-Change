#pragma once

#include <cmath>

class Maths {
public:
  Maths() {};
  ~Maths() {};

  static double NRoot(const double v, const double n) {
    double out = v;
    const double exp = 1. / n;
    if (std::fmod(n, 1.) == 0.) {
      out = std::pow(out, exp);
    }
    else {
      double absroot = std::pow(std::abs(out), exp);
      if (out < 0.) absroot *= -1.;
      out = absroot;
    }
    return out;
  }

  static double UnsignedMod(const double numer, const double denom) {
    return std::fmod(std::fmod(numer, denom) + denom, denom);
  }

  static const double Pi;
  static const double Tau;
  static const double RadToDeg;
};