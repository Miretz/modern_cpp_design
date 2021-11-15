#include "functor.h"

class Parrot {
public:
  void eat() { std::cout << "Tsk, knick, tsk...\n"; }
  void speak() { std::cout << "Oh Captain, my Captain!\n"; }
};

auto main() -> int {

  Parrot geronimo;

  Functor<> cmd1(&geronimo, &Parrot::eat);
  Functor<> cmd2(&geronimo, &Parrot::speak);

  cmd1();
  cmd2();

  return 0;
}
