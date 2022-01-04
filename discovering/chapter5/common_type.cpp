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

int main()
{
  auto s = minimum(-7, 3.6f, 9u, -42.6);
  std::cout << "s is " << s << " and its type is " << typeid(s).name() << '\n';

  return 0;
}
