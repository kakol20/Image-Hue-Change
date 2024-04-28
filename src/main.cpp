// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello World\n";

  double tempArr[] = {
    1., 2., 1.,
    0., 1., 0.,
    2., 3., 4.
  };

  Matrix lhs(tempArr, 3, 3);
  Matrix lhsInv = lhs;
  lhsInv.Invert3x3();

  //tempArr = { 1 };

  //std::cout <<
  std::cout << lhs.Debug();
  std::cout << lhsInv.Debug();

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}