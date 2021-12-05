#include <cmath>
#include <iostream>

template <typename F, typename T> class derivative {
  public:
    derivative(const F &f, const T &h) : f(f), h(h) {}
    T operator()(const T &x) const { return (f(x + h) - f(x)) / h; }

  private:
    const F &f;
    T h;
};

class psc_f {
  public:
    explicit psc_f(double alpha) : alpha(alpha) {}
    double operator()(double x) const {
        return std::sin(alpha + x) + std::cos(x);
    }

  private:
    double alpha;
};

template <typename F, typename T> class second_derivative {
  public:
    second_derivative(const F &f, const T &h) : h(h), fp(f, h) {}
    T operator()(const T &x) const { return (fp(x + h) - fp(x)) / h; }

  private:
    T h;
    derivative<F, T> fp;
};

auto main() -> int {
    using d_psc_f = derivative<psc_f, double>;
    psc_f psc_o(1.0);
    d_psc_f d_psc_o(psc_o, 0.001);
    std::cout << "der. of sin(0) + cos(0) is " << d_psc_o(0.0) << '\n';
    std::cout << "der. of sin(1) + cos(1) is " << d_psc_o(1.0) << '\n';

    second_derivative<psc_f, double> dd_psc_2_o(psc_f(1.0), 0.001);
    std::cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_2_o(0.0) << '\n';

    return 0;
}