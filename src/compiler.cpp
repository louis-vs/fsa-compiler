#include <iostream>
#include <fstream>

int main() {
  std::ifstream file("test\\fsa_code");

  std::string line;
  std::getline(file, line);

  std::cout << line;

  file.close();
  return 0;
}