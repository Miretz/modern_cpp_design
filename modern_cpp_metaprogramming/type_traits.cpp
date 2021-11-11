#include <iostream>
#include <type_traits>

int add(int a, int b) { return a + b; }

using AddPtr = int (*)(int, int);

using Array1 = int[2];    // int       [2]
using Array2 = Array1[3]; // int    [3][2]
using Array3 = Array2[5]; // int [5][3][2]

using std::cout;

auto main() -> int {
  cout << std::is_same_v<decltype(add), AddPtr> << '\n';  // false
  cout << std::is_same_v<decltype(&add), AddPtr> << '\n'; // true
  cout << std::is_function_v<AddPtr> << '\n';             // false
  cout << std::is_pointer_v<AddPtr> << '\n';              // true

  cout << std::is_function_v<std::remove_pointer_t<AddPtr>> << '\n'; // true

  cout << std::rank_v<Array1> << '\n';  // gives dimension of the array

  cout << std::extent_v<Array1, 0> << '\n'; // 2 
  cout << std::extent_v<Array2, 0> << '\n'; // 3

  std::remove_extent_t<Array3> A2; // == Array2
  std::remove_extent_t<Array2> A1; // == Array1

  std::remove_all_extents_t<Array3> A; // == int;

  return 0;
}
