#include <iostream>
#include <type_traits>

#include "../loki-0.1.7/include/loki/Typelist.h"

using Loki::NullType;
using Loki::Typelist;
using namespace Loki::TL;

// Erase specific type - stops when found

template <class TList, class T> struct MyErase;

template <class T> struct MyErase<NullType, T> { typedef NullType Result; };

template <class T, class Tail> struct MyErase<Typelist<T, Tail>, T> {
  typedef Tail Result;
};

template <class Head, class Tail, class T>
struct MyErase<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename MyErase<Tail, T>::Result> Result;
};

// Erase all occurences - continues to find all occurences

template <class TList, class T> struct MyEraseAll;

template <class T> struct MyEraseAll<NullType, T> { typedef NullType Result; };

template <class T, class Tail> struct MyEraseAll<Typelist<T, Tail>, T> {
  typedef typename MyEraseAll<Tail, T>::Result Result;
};

template <class Head, class Tail, class T>
struct MyEraseAll<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename MyEraseAll<Tail, T>::Result> Result;
};

// Erasing duplicates

template <class TList> struct MyNoDuplicates;

template <> struct MyNoDuplicates<NullType> { typedef NullType Result; };

template <class Head, class Tail> struct MyNoDuplicates<Typelist<Head, Tail>> {
private:
  typedef typename MyNoDuplicates<Tail>::Result L1;
  typedef typename MyErase<L1, Head>::Result L2;

public:
  typedef Typelist<Head, L2> Result;
};

// Example

auto main() -> int {
  typedef Typelist<
      signed char,
      Typelist<
          short int,
          Typelist<int, Typelist<long int, Typelist<int, Typelist<signed char,
                                                                  NullType>>>>>>
      MyList;

  typedef MyErase<MyList, signed char>::Result MyListNoChar;
  typedef MyEraseAll<MyList, int>::Result MyListNoInt;
  typedef MyNoDuplicates<MyList>::Result MyListDedup;

  std::cout << "Original Length: " << Length<MyList>::value << '\n';
  std::cout << "Removed 1 type: " << Length<MyListNoChar>::value << '\n';
  std::cout << "Removed all int (2 occurences): " << Length<MyListNoInt>::value
            << '\n';
  std::cout << "Deduplicated list: " << Length<MyListDedup>::value << '\n';

  return 0;
}
