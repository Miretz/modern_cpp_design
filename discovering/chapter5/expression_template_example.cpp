#include <iostream>

template <typename T> class vector_sum;

template <typename T> struct vector {
    T data[3];
    T operator[](int i) const { return data[i]; }
    vector &operator=(const vector_sum<T> &that) {
        for (int i = 0; i < 3; ++i) {
            data[i] = that[i];
        }
        return *this;
    }
};

template <typename T> class vector_sum {
  public:
    vector_sum(const vector<T> &v1, const vector<T> &v2) : v1(v1), v2(v2) {}

    friend int size(const vector_sum &x) { return size(x.v1); }
    T operator[](int i) const { return v1[i] + v2[i]; }

  private:
    const vector<T> &v1, &v2;
};

template <typename T> class vector_sum3 {
  public:
    vector_sum3(const vector<T> &v1, const vector<T> &v2, const vector<T> &v3)
        : v1(v1), v2(v2), v3(v3) {}
    T operator[](int i) const { return v1[i] + v2[i] + v3[i]; }

  private:
    const vector<T> &v1, &v2, &v3;
};

template <typename T>
vector_sum3<T> inline operator+(vector_sum<T> &x, const vector<T> &y) {
    return {x.v1, x.v2, y};
}

auto main() -> int {
    vector<int> a{{1, 2, 3}};
    vector<int> b{{2, 2, 6}};
    vector<int> c{{7, 6, 5}};

    vector_sum3<int> add3{a, b, c};

    std::cout << "Result: ( ";
    for (int i = 0; i < 3; ++i) {
        std::cout << add3[i] << " ";
    }
    std::cout << ")\n";

    return 0;
}