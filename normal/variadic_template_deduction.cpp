#include <iostream>

template <class T, class... Us> void f([[maybe_unused]] Us... us) {
  puts(__PRETTY_FUNCTION__);
}

template <class... Ts, class U> void g([[maybe_unused]] U u) {
  puts(__PRETTY_FUNCTION__);
}

auto main() -> int {

  f<char>(0, 1, 2);
  f<char, char>(0, 1, 2);

  g<int, char>(3.1);

  return 0;
}
