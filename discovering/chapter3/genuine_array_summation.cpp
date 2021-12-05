#include <iostream>

// the compiler can deduce the array size [N]
template <typename T, unsigned N> T sum(const T (&array)[N]) {
    T result(0);
    for (unsigned i = 0; i < N; ++i) {
        result += array[i];
    }
    return result;
}

// alternative version
template <typename T> inline T accumulate_array(T *a, T *a_end) {
    T result(0);
    for (; a != a_end; ++a) {
        result += *a;
    }
    return result;
}

auto main() -> int {
    int ai[] = {2, 4, 7};
    double ad[] = {2., 4.5, 7.};

    std::cout << "sum ai is " << sum(ai) << '\n';
    std::cout << "sum ad is " << sum(ad) << '\n';

    std::cout << "sum ai is " << accumulate_array(ai, &ai[3]) << '\n';
    std::cout << "sum ad is " << accumulate_array(ad, &ad[3]) << '\n';
}