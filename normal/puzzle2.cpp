#include <iostream>

template <typename R, typename A> void foo(R (*fptr)(A)) {
  puts(__PRETTY_FUNCTION__);
}

auto main() -> int {
  // foo([](double x) { return int(x); });
  foo(+[](double x) { return int(x); });
  return 0;
}
