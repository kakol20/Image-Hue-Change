// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  //std::cout << "Hello World\n";

  //std::cout << "Have " << argc << " arguments:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << '\n';
  }
  std::cout << '\n';

  sRGB t1(1., 0., 0.5);
  sRGB t2 = t1;
  t2 *= t1;
  sRGB t3 = t2 * (1. / 3.);

  std::cout << t1.Debug() << '\n';
  std::cout << t2.Debug() << '\n';
  std::cout << t3.Debug() << '\n';

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}