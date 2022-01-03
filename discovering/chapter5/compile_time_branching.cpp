#include <iostream>
#include <typeinfo>

// can be also found in <type_traits>

template <bool Condition, typename ThenType, typename ElseType>
struct conditional
{
  using type = ThenType;
};

template <typename ThenType, typename ElseType>
struct conditional<false, ThenType, ElseType>
{
  using type = ElseType;
};

// type alias for the above structs
template <bool b, class T, class F>
using conditional_t = typename conditional<b, T, F>::type;

int main()
{
  constexpr auto max_iter = 320;

  // if max_iter is more than 100 we will use double, otherwise we will use float
  using tmp_name = typename conditional<(max_iter > 100), double, float>::type;
  std::cout << "typeid = " << typeid(tmp_name).name() << '\n';

  using tmp_name_2 = typename conditional<(max_iter > 1000), double, float>::type;
  std::cout << "typeid = " << typeid(tmp_name_2).name() << '\n';

  // using type alias
  conditional_t<false, int, char> int_or_char;
  std::cout << "typeid = " << typeid(int_or_char).name() << '\n';
  
  return 0;
}

