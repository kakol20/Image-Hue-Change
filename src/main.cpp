// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello World\n";

  Matrix lhs({
    1., 2., 1.,
    0., 1., 0.,
    2., 3., 4.}, 3, 3);
  Matrix rhs({
    2, 5,
    6, 7,
    1, 8}, 2, 3);
  Matrix lhsInv = lhs;
  lhsInv.Invert3x3();

  Matrix mult = lhs * rhs;
  Matrix multInv = lhsInv * mult;

  //tempArr = { 1 };

  //std::cout <<
  std::cout << lhs.Debug();
  std::cout << rhs.Debug();
  std::cout << lhsInv.Debug();
  std::cout << mult.Debug();
  std::cout << multInv.Debug();

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}