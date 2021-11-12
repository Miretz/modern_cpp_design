#include <iostream>

class Parrot {
public:
  void eat() { std::cout << "Tsk, knick, tsk...\n"; }
  void speak() { std::cout << "Oh Captain, my Captain!\n"; }
};

auto main() -> int {
  typedef void (Parrot::*tp_mem_fun)();
  tp_mem_fun p_activity = &Parrot::eat;

  Parrot geronimo;
  Parrot *p_geronimo = &geronimo;

  (geronimo.*p_activity)();
  (p_geronimo->*p_activity)();

  p_activity = &Parrot::speak;

  (geronimo.*p_activity)();

  return 0;
}
