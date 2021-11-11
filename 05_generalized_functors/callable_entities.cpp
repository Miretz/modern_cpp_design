#include <iostream>

void floo() { std::cout << "floo called\n"; }

void barl() { std::cout << "barl called\n"; }

auto main() -> int {

  void (*p_floo)() = &floo;

  floo();
  barl();
  (*p_floo)();

  void (*p_floo_2)() = p_floo;
  p_floo = &barl;

  (*p_floo)();
  (*p_floo_2)();

  p_floo();
  p_floo_2();

  return 0;
}
