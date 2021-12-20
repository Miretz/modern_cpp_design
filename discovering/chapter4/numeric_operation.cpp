#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int {
    std::vector<float> v = {3.1, 4.2, 7, 9.3, 2, 5, 7, 8, 3, 4};
    std::vector<float> w(10), x(10), y(10);

    // generates a sequence from starting number incrementing by 1
    std::iota(w.begin(), w.end(), 12.1);

    // generates a sequence of partial sums of v into x
    std::partial_sum(v.begin(), v.end(), x.begin());

    std::adjacent_difference(v.begin(), v.end(), y.begin());

    // inner_product computes the default dot product
    float alpha = std::inner_product(w.begin(), w.end(), v.begin(), 0.0f);

    float sum_w = std::accumulate(w.begin(), w.end(), 0.0f);

    float product_w = std::accumulate(w.begin(), w.end(), 1.0f,
                                      [](float x, float y) { return x * y; });

    std::cout << "Alpha: " << alpha;
    std::cout << " Sum of W: " << sum_w;
    std::cout << " Product of W: " << product_w << '\n';

    return 0;
}