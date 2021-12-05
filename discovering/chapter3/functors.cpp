#include <cmath>
#include <iostream>

// implement the finite difference of a differentiable function

// using function pointers

double fin_diff_fp(double f(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

double sin_plus_cos(double x) { return std::sin(x) + std::cos(x); }

void example_function_pointers() {
    std::cout << fin_diff_fp(sin_plus_cos, 1., 0.001) << '\n';
    std::cout << fin_diff_fp(sin_plus_cos, 0., 0.001) << '\n';
}

// what if we wanted to call fin_diff with fin_diff as argument
// we can only solve this via Functors

struct sin_plus_cos_functor {
    double operator()(double x) const { return std::sin(x) + std::cos(x); }
};

// functors could also hold our parameters
class parametrized_sin_plus_cos_functor {
  public:
    explicit parametrized_sin_plus_cos_functor(double alpha) : alpha(alpha) {}
    double operator()(double x) const {
        return std::sin(alpha + x) + std::cos(x);
    }

  private:
    double alpha;
};

// generic fin_diff that acceptrs functors
template <typename F, typename T>
T inline fin_diff(F f, const T &x, const T &h) {
    return (f(x + h) - f(x)) / h;
}

void example_functors() {
    parametrized_sin_plus_cos_functor psc_o(1.0);
    std::cout << fin_diff(psc_o, 1., 0.001) << '\n';
    std::cout << fin_diff(parametrized_sin_plus_cos_functor(2.0), 1., 0.001)
              << '\n';
    std::cout << fin_diff(sin_plus_cos, 0., 0.001) << '\n';
}

auto main() -> int {
    example_function_pointers();
    example_functors();
    return 0;
}