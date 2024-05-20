// main.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <sstream>
#include <chrono>

#include "colourSpace/ColourSpace.hpp"
#include "colourSpace/OkLCh.h"
#include "colourSpace/sRGB.hpp"
#include "maths/Maths.hpp"
#include "maths/Matrix.h"
#include "misc/Log.h"
#include "misc/Pseudo2DArray.hpp"

const double Maths::Pi = 3.1415926535;
const double Maths::Tau = 6.283185307;
const double Maths::RadToDeg = 180. / Maths::Pi;
const double Maths::DegToRad = Maths::Pi / 180.;

int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    Log::StartLine();

    std::stringstream ss;
    ss << argv[i];
    Log::Write(ss.str());
    Log::EndLine();
  }

  Log::StartTime();
  while (true) {
    if (Log::CheckTimeSeconds(5.)) {
      Log::StartLine();
      Log::Write("5 seconds later");
      Log::EndLine();

      break;
    }
  }

  Log::StartTime();
  while (true) {
    if (Log::CheckTimeSeconds(2. / 24.)) {
      Log::StartLine();
      Log::Write("2 frames later (24fps)");
      Log::EndLine();

      break;
    }
  }

  Log::Save();

  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}