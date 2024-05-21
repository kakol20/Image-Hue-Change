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
      Log::Write("Input: " + input);
      Log::EndLine();

      std::string output = settings["output"];
      Log::StartLine();
      Log::Write("Output: " + output);
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

        // ----- PROCESS IMAGE -----

        OkLCh diff = tgt_col - ref_col;
        diff = OkLCh(0, 0, diff.GetH());
        Log::StartLine();
        Log::Write("Difference: OkLCh(");
        Log::Write(diff.Debug());
        Log::Write(")");
        //Log::EndLine();

        Log::StartTime();
        for (int y = 0; y < inputImage.GetHeight(); y++) {
          for (int x = 0; x < inputImage.GetWidth(); x++) {
            const size_t index = inputImage.GetIndex(x, y);

            // ----- READ PIXEL COLOUR -----

            sRGB pixelsRGB;
            if (grayscale) {
              double v = sRGB::UInt8ToDouble(inputImage.GetData(index));
              pixelsRGB = sRGB(v, v, v);
            }
            else {
              double r = sRGB::UInt8ToDouble(inputImage.GetData(index + 0));
              double g = sRGB::UInt8ToDouble(inputImage.GetData(index + 1));
              double b = sRGB::UInt8ToDouble(inputImage.GetData(index + 2));
              pixelsRGB = sRGB(r, g, b);
            }

            OkLCh pixelLCh = OkLCh::sRGBtoOkLCh(pixelsRGB);
            pixelLCh += diff;
            pixelLCh.Fallback();

            // ----- WRITE PIXEL COLOUR -----

            pixelsRGB = OkLCh::OkLChtosRGB(pixelLCh);
            if (grayscale) {
              uint8_t v = pixelsRGB.GetRUInt();
              inputImage.SetData(index, v);
            }
            else {
              uint8_t r = pixelsRGB.GetRUInt();
              uint8_t g = pixelsRGB.GetGUInt();
              uint8_t b = pixelsRGB.GetBUInt();
              
              inputImage.SetData(index + 0, r);
              inputImage.SetData(index + 1, g);
              inputImage.SetData(index + 2, b);
            }

            // ----- CHECK PROCESS TIME -----

            if (Log::CheckTimeSeconds(0.1)) {
              double progress = double(index) / double(inputImage.GetSize());
              progress *= 100;

              Log::EndLine();
              Log::StartLine();
              Log::Write("  ");
              Log::Write(std::to_string(progress));
              Log::Write("%");

              Log::StartTime();
            }
          }
        }
        Log::EndLine();

        inputImage.Write(output.c_str());
      }
    }
  }

  Log::Save();
  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}