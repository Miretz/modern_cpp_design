#include <iostream>

template <typename Type> Type read_input() {
  Type obj;
  std::cin >> obj;
  return obj;
}

template <typename Type> constexpr Type factorial(Type value) {
  Type result = 1;
  while (value > 0) {
    result *= value;
    --value;
  }
  return result;
}

auto main() -> int {

  std::cout << "Enter a whole number: ";
  const auto n = read_input<long>();
  const auto fact = factorial<long>(n);

  std::cout << "\nFactorial of " << n << " = " << fact << '\n';
  return 0;
}
