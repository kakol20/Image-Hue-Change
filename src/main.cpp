// main.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "colourSpace/ColourSpace.hpp"
#include "colourSpace/OkLCh.h"
#include "colourSpace/sRGB.hpp"
#include "maths/Maths.hpp"
#include "maths/Matrix.h"
#include "misc/Pseudo2DArray.hpp"

const double Maths::Pi = 3.1415926535;
const double Maths::Tau = 6.283185307;
const double Maths::RadToDeg = 180. / Maths::Pi;

int main(int argc, char* argv[]) {
  //std::cout << "Hello World\n";

  //std::cout << "Have " << argc << " arguments:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << '\n';
  }
  std::cout << '\n';

  std::cout << Maths::Pi << ' ' << Maths::Tau << ' ' << Maths::RadToDeg << '\n';

  sRGB t1(56. / 255., 140. / 255., 70 / 255.);
  sRGB t2 = t1;
  t2 *= t1;
  sRGB t3 = t2 * (1. / 3.);

  OkLCh t4 = OkLCh::sRGBtoOkLCh(t1);
  sRGB t5 = OkLCh::OkLChtosRGB(t4);
  OkLCh t6(0., 0., Maths::Pi);
  t6 += t4;

  std::cout << t1.Debug() << '\n';
  std::cout << t2.Debug() << '\n';
  std::cout << t3.Debug() << '\n';
  std::cout << t4.Debug(true) << '\n';
  std::cout << t5.Debug() << '\n';
  std::cout << t6.Debug(true) << '\n';

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}