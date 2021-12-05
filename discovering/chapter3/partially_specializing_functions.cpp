#include <complex>
#include <iostream>

// functor allows us to specialize "functions"
template <typename T> struct abs_functor;

// generic abs function
template <typename T> decltype(auto) abs(const T &x) {
    return abs_functor<T>()(x);
}

// partial specialization for real numbers
template <typename T> struct abs_functor {
    T operator()(const T &x) { return x < T(0) ? -x : x; }
};

// partial specialization for std::complex number
template <typename T> struct abs_functor<std::complex<T>> {
    T operator()(const std::complex<T> &x) {
        return std::sqrt(real(x) * real(x) + imag(x) * imag(x));
    }
};

auto main() -> int {

    std::cout << "abs(-44) = " << abs(-44) << '\n';
    std::cout << "abs(std::complex<double>(-4.4,2.2)) = "
              << abs(std::complex<double>(-4.4, 2.2)) << '\n';

    return 0;
}
