#include <fstream>
#include <iostream>
#include <sstream>

auto write_something(std::ostream &os) {
  os << "Hi stream, did you know that 3 * 3 = " << 3 * 3 << std::endl;
}

auto main() -> int {

  std::ofstream myfile("example.txt");
  std::stringstream mysstream;

  write_something(std::cout);
  write_something(myfile);
  write_something(mysstream);

  std::cout << "mysstream is: " << mysstream.str();

  // printing booleans
  std::cout << std::boolalpha << (2 < 3) << '\n';

  return 0;
}
