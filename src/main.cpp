#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../ext/json/json.hpp"
#include "colourSpace/ColourSpace.hpp"
#include "colourSpace/OkLCh.h"
#include "colourSpace/sRGB.hpp"
#include "image/Image.h"
#include "maths/Maths.hpp"
#include "maths/Matrix.h"
#include "misc/Log.h"
#include "misc/Pseudo2DArray.hpp"

using json = nlohmann::json;

const double Maths::Pi = 3.1415926535;
const double Maths::Tau = 6.283185307;
const double Maths::RadToDeg = 180. / Maths::Pi;
const double Maths::DegToRad = Maths::Pi / 180.;

int main() {
  // ----- CHECK IF settings.json EXISTS -----

  std::ifstream f("settings.json");
  if (f.fail()) {
    Log::StartLine();
    Log::Write("settings.json not found");
    Log::EndLine();
  }
  else {
    json settings = json::parse(f);

    // ----- CHECK IF SETTING EXISTS -----

    bool success = true;

    if (!settings.contains("input")) {
      Log::StartLine();
      Log::Write("input setting not found");
      Log::EndLine();
      success = false;
    }

    if (!settings.contains("output")) {
      Log::StartLine();
      Log::Write("output setting not found");
      Log::EndLine();
      success = false;
    }

    if (!settings.contains("ref_col")) {
      Log::StartLine();
      Log::Write("ref_col setting not found");
      Log::EndLine();
      success = false;
    }

    if (!settings.contains("tgt_col")) {
      Log::StartLine();
      Log::Write("tgt_col setting not found");
      Log::EndLine();
      success = false;
    }

    if (success) {
      // ----- READ SETTINGS -----

      std::string input = settings["input"];
      Log::StartLine();
      Log::Write("input: " + input);
      Log::EndLine();

      std::string output = settings["output"];
      Log::StartLine();
      Log::Write("output: " + output);
      Log::EndLine();

      OkLCh ref_col = OkLCh::sRGBtoOkLCh(sRGB::HexTosRGB(settings["ref_col"]));
      Log::StartLine();
      Log::Write("Reference Colour: #");
      Log::Write(settings["ref_col"]);
      Log::Write(" OkLCh(");
      Log::Write(ref_col.Debug());
      Log::Write(")");
      Log::EndLine();

      OkLCh tgt_col = OkLCh::sRGBtoOkLCh(sRGB::HexTosRGB(settings["tgt_col"]));
      Log::StartLine();
      Log::Write("Target Colour: #");
      Log::Write(settings["tgt_col"]);
      Log::Write(" OkLCh(");
      Log::Write(tgt_col.Debug());
      Log::Write(")");
      Log::EndLine();

      // ----- READ INPUT IMAGE -----

      success = true;
      Image inputImage;
      if (!inputImage.Read(input.c_str())) success = false;

      if (success) {
        Log::StartLine();
        bool grayscale = false;
        if (inputImage.GetChannels() <= 2) {
          Log::Write("  Is Grayscale: TRUE");
          grayscale = true;
        }
        else {
          Log::Write("  Is Grayscale: FALSE");
        }
        Log::EndLine();

        Log::StartLine();
        bool alpha = false;
        if (inputImage.GetChannels() == 2 || inputImage.GetChannels() == 4) {
          Log::Write("  Has Alpha: TRUE");
          alpha = true;
        }
        else {
          Log::Write("  Has Alpha: FALSE");
        }
        Log::EndLine();
      }
    }
  }

  Log::Save();
  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}