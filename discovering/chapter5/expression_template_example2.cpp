#include <iostream>
#include <type_traits>

template <typename V1, typename V2> class vector_sum {
  public:
    vector_sum(const V1 &v1, const V2 &v2) : v1(v1), v2(v2) {}

    using value_type =
        std::common_type_t<typename V1::value_type, typename V2::value_type>;
    value_type operator[](int i) const { return v1[i] + v2[i]; }

  private:
    const V1 &v1;
    const V2 &v2;
};

template <typename V1, typename V2>
inline vector_sum<V1, V2> operator+(const V1 &x, const V2 &y) {
    return {x, y};
}

template <typename T> struct vector {
    T data[3];
    T operator[](int i) const { return data[i]; }

    using value_type = T;

    template <typename Src> vector &operator=(const Src &that) {
        for (int i = 0; i < 3; ++i) {
            data[i] = that[i];
        }
        return *this;
    }
};

auto main() -> int {
    vector<int> a{{1, 2, 3}};
    vector<int> b{{2, 5, 6}};
    vector<int> c{{7, 6, 5}};

    auto w = a + b + c;

    std::cout << "Result: ( ";
    for (int i = 0; i < 3; ++i) {
        std::cout << w[i] << " ";
    }
    std::cout << ")\n";

    return 0;
}