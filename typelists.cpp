#include <iostream>

#include "loki-0.1.7/include/loki/Typelist.h"

using Loki::Typelist;
using namespace Loki::TL;

class NullType {};

auto main() -> int {
  typedef Typelist<char, Typelist<signed char, unsigned char>> CharList;

  typedef Typelist<int, NullType> OneTypeOnly;

  typedef Typelist<
      signed char,
      Typelist<short int, Typelist<int, Typelist<long int, NullType>>>>
      SignedIntegrals;

  CharList::Head a = 'a';
  OneTypeOnly::Head b = 12;
  SignedIntegrals::Head c = 'c';

  std::cout << a << ' ' << b << ' ' << c << '\n';

  return 0;
}
