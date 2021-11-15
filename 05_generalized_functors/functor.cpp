#include "functor.h"

// Test Functor

struct TestFunctor {
  void operator()(int i, double d) {
    std::cout << "TestFunctor::operator()(" << i << ", " << d << ") called.\n";
  }
};

struct TestFunctor2 {
  int operator()(int a, int b) { return a * b; }
};

// Test Function

void test_function(int i, double d) {
  std::cout << "test_function(" << i << ", " << d << ") called.\n";
}

auto main() -> int {
  TestFunctor f;
  Functor<void, LOKI_TYPELIST_2(int, double)> cmd(f);
  cmd(4, 4.5);

  TestFunctor2 f2;
  Functor<int, LOKI_TYPELIST_2(int, int)> cmd_mul(f2);
  std::cout << cmd_mul(6, 4) << '\n';

  Functor<void, LOKI_TYPELIST_2(int, double)> cmd_fun(&test_function);
  cmd_fun(5, 5.5);

  return 0;
}
