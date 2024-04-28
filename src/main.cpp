// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  //std::cout << "Hello World\n";

  Matrix lhs({
    0.4124564, 0.3575761, 0.1804375,
    0.2126729, 0.7151522, 0.0721750,
    0.0193339, 0.1191920, 0.9503041 }, 3, 3);
  Matrix rhs({ 1,0.5,0.25, }, 1, 3);
  Matrix lhsInv = lhs;
  if (!lhsInv.Invert3x3()) std::cout << "Matrix inversion failed\n";

  Matrix mult = lhs * rhs;
  Matrix multInv = lhsInv * mult;

  //std::cout <<
  std::cout << lhs.Debug() << '\n';
  std::cout << rhs.Debug() << '\n';
  std::cout << lhsInv.Debug() << '\n';
  std::cout << mult.Debug() << '\n';
  std::cout << multInv.Debug() << '\n';

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}