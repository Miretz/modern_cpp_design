#include <iostream>
#include <type_traits>

template <bool Condition, typename ReturnType = void> struct enable_if {};

template <typename ReturnType> struct enable_if<true, ReturnType> {
  using type = ReturnType;
};

template <bool Condition, typename ReturnType = void>
using enable_if_t = typename enable_if<Condition, ReturnType>::type;

// usage
template <typename T>
auto call_num(T num) -> enable_if_t<std::is_integral_v<T>, T> {
  std::cout << "Integer: " << num << '\n';
  return num;
}

template <typename T>
auto call_num(T num) -> enable_if_t<std::is_floating_point_v<T>, T> {
  std::cout << "Float: " << num << '\n';
  return num;
}

template <typename T>
auto call_num(T num) -> enable_if_t<std::is_pointer_v<T>, T> {
  std::cout << "const char*: " << num << '\n';
  return num;
}

auto main() -> int {

  call_num(42);
  call_num(5.0);
  call_num("wot");

  return 0;
}
