#include <cmath>
#include <iostream>

template <typename F, typename T> class derivative {
  public:
    explicit derivative(const F &f, const T &h) : f(f), h(h) {}
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

// recursive composing
template <typename F, typename T, unsigned N> class nth_derivative {
    using prev_derivative = nth_derivative<F, T, N - 1>;

  public:
    nth_derivative(const F &f, const T &h) : h(h), fp(f, h) {}
    T operator()(const T &x) const {
        return (N & 1) ? ((fp(x + h) - fp(x)) / h) : ((fp(x) - fp(x - h)) / h);
    }

  private:
    T h;
    prev_derivative fp;
};

// recursion termination specialization
template <typename F, typename T>
class nth_derivative<F, T, 1> : public derivative<F, T> {
    // since the implemenation is the same as derivative we reuse it's
    // definitions
    using derivative<F, T>::derivative;
};

// convenience make function which deduces the types of T and F
template <unsigned N, typename F, typename T>
nth_derivative<F, T, N> make_nth_derivative(const F &f, const T &h) {
    return nth_derivative<F, T, N>(f, h);
}

auto main() -> int {
    using d_psc_f = derivative<psc_f, double>;
    psc_f psc_o(1.0);
    d_psc_f d_psc_o(psc_o, 0.001);
    std::cout << "der. of sin(0) + cos(0) is " << d_psc_o(0.0) << '\n';
    std::cout << "der. of sin(1) + cos(1) is " << d_psc_o(1.0) << '\n';

    nth_derivative<psc_f, double, 22> d22_psc_o(psc_f(1.0), 0.00001);
    std::cout << "22nd der. of sin(0) + cos(0) is " << d22_psc_o(0.0) << '\n';

    auto d7_psc_o = make_nth_derivative<7>(psc_o, 0.0001);
    std::cout << "7th der. of sin(0) + cos(0) is " << d7_psc_o(0.0) << '\n';

    return 0;
}