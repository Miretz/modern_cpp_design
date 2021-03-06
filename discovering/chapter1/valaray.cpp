#include <iostream>
#include <valarray>

auto main() -> int {

  // valarray allows element-wise arithmentic operations
  std::valarray<float> v = {1, 2, 3}, w = {7, 8, 9}, s = v + 2.0f * w;
  v = sin(s);
  for (float x : v)
    std::cout << x << ' ';
  std::cout << '\n';
  return 0;
}
