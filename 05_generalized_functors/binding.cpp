#include "functor.h"

void test(int i, int j) {
  std::cout << "called test() with: " << i << ' ' << j << '\n';
  std::cout << __PRETTY_FUNCTION__ << "\n\n";
}

auto main() -> int {

  Functor<void, LOKI_TYPELIST_2(int, int)> cmd1(&test);

  Functor<void, LOKI_TYPELIST_1(int)> cmd2(BindFirst(cmd1, 10));
  cmd2(20);

  Functor<void> cmd3(BindFirst(cmd2, 30));
  cmd3();
}
