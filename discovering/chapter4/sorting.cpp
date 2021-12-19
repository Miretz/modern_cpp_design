#include <algorithm>
#include <complex>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

auto main() -> int {
    std::vector<int> seq = {3, 4, 7, 9, 2, 5, 6, 7, 8, 3, 4, 3, 2, 9};
    std::sort(seq.begin(), seq.end(), [](int x, int y) { return x > y; });

    // sorting complex numbers
    using cf = std::complex<float>;
    std::vector<cf> v = {{3, 4}, {7, 9}, {2, 5}, {7, 8}};
    std::sort(v.begin(), v.end(), [](cf x, cf y) { return abs(x) < abs(y); });

    // lexicographic order lambda
    auto lex = [](cf x, cf y) {
        return (real(x) < real(y)) || (real(x) == real(y) && imag(x) < imag(y));
    };
    std::sort(v.begin(), v.end(), lex);

    std::copy(seq.begin(), seq.end(),
              std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    std::copy(v.begin(), v.end(), std::ostream_iterator<cf>(std::cout, ", "));
    std::cout << std::endl;

    return 0;
}