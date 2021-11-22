#include <iostream>
#include <string>
#include <fstream>

auto main() -> int {

  int age;
  std::cout << "What is your age? ";
  std::cin >> age;

  std::cout << "Your age is " << age << std::endl;

  std::ofstream age_file{"age.txt"};
  age_file << age << std::endl;

  return 0;
}
