// main.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello World\n";

  Pseudo2DArray<double> mat(3, 3);

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();
  return 0;
}