#include <iostream>
#include <type_traits>

#include "loki-0.1.7/include/loki/Typelist.h"

using Loki::Typelist;
using Loki::NullType;
using namespace Loki::TL;

template <class TList, unsigned int index> struct MyTypeAt;

template <class Head, class Tail> struct MyTypeAt<Typelist<Head, Tail>, 0> {
  typedef Head Result;
};
template <class Head, class Tail, unsigned int i>
struct MyTypeAt<Typelist<Head, Tail>, i> {
  typedef typename MyTypeAt<Tail, i - 1>::Result Result;
};

auto main() -> int {
  typedef Typelist<
      signed char,
      Typelist<short int, Typelist<int, Typelist<long int, NullType>>>>
      SignedIntegrals;

  MyTypeAt<SignedIntegrals, 1>::Result s = 122; // short int
  MyTypeAt<SignedIntegrals, 3>::Result l = 122; // long int

  std::cout << typeid(s).name() << '\n' << typeid(l).name() << '\n';

  return 0;
}
