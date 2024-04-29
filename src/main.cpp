// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  //std::cout << "Hello World\n";

  sRGB t1(1., 0., 0.);
  sRGB t2 = t1 * 0.5;

  std::cout << t1.Debug() << '\n';
  std::cout << t2.Debug() << '\n';

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}