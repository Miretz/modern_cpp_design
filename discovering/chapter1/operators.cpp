#include <iostream>

auto main() -> int {

  const float r1 = 3.5, r2 = 7.3, pi = 3.14159;

  float area1 = pi * r1 * r1;

  std::cout << "A circle of radius " << r1 << " has area " << area1 << "."
            << std::endl;

  std::cout << "The average of " << r1 << " and " << r2 << " is "
            << (r1 + r2) / 2 << "." << std::endl;

  // example of precision issues
  long l = 1234567890123;
  long l2 = l + 1.0f - 1.0;
  long l3 = l + (1.0f - 1.0);

  std::cout << "l: " << l << " l2: " << l2 << " l3: " << l3 << std::endl;

  return 0;
}
