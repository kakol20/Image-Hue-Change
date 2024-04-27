// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello World\n";

  Pseudo2DArray<double> mat(3, 3);
  mat(0, 0) = 3.14159265;
  std::cout << mat(0, 0) << std::endl;
  mat(0, 0) *= 2.;
  std::cout << mat(0, 0) << std::endl;

  const Pseudo2DArray<double> matC = mat;
  //double test = matC(0, 0);
  std::cout << matC(0, 0) << std::endl;

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}