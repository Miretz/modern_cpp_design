#include <iostream>
#include <cmath>
#include <complex>

template <typename T>
T inline min_magnitude(const T& x, const T& y)
{
  using std::abs;
  auto ax = abs(x), ay = abs(y);
  return ax < ay ? x : y;
}

int main()
{
  double d1 = 3., d2 = 4.;
  std::cout << "min |d1, d2| = " << min_magnitude(d1, d2) << '\n';

  std::complex<double> c1(3.), c2(4.);
  std::cout << "min |c1, c2| = " << min_magnitude(c1, c2) << '\n';

  return 0;
}
