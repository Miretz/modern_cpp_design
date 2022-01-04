#include <iostream>
#include <type_traits>

template <typename T>
inline T minimum(const T& t) { return t; }

template <typename T, typename ...P>
typename std::common_type<T, P...>::type
minimum(const T& t, const P& ...p)
{
  typedef typename std::common_type<T, P...>::type res_type;
  return std::min(res_type(t), res_type(minimum(p...)));
}

// In C++14 the variadic overload of minimum simplifies the definition
// using auto keyword

template <typename T, typename ...P>
inline auto minimum_new(const T& t, const P& ...p)
{
  using res_type = std::common_type_t<T, P...>;
  return std::min(res_type(t), res_type(minimum(p...)));
}

int main()
{
  auto s = minimum(-7, 3.6f, 9u, -42.6);
  std::cout << "s is " << s << " and its type is " << typeid(s).name() << '\n';

  auto s2 = minimum_new(-7, 3.6f, 9u, -42.6);
  std::cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << '\n';
  
  return 0;
}
