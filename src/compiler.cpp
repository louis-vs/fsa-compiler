#include <iostream>
#include <fstream>

class Parser {
  // take stream as input
  // read each line
  // build program tree
  // is effectively itself going to be like an FSA
  // three states: read states; read symbols; read transitions
};

int main() {
  std::ifstream file("test\\fsa_code");

  std::string line;
  std::getline(file, line);

  std::cout << line;

  file.close();
  return 0;
}