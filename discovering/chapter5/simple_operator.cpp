#include <iostream>

// we could simply use operator overloading
// but in this case an inline function migth be faster

template <typename T> struct vector { T data[3]; };

template <typename T>
void inline add3(const vector<T> &x, const vector<T> &y, const vector<T> &z,
                 vector<T> &sum) {
    for (int i = 0; i < 3; ++i) {
        sum.data[i] = x.data[i] + y.data[i] + z.data[i];
    }
}

auto main() -> int {
    // it's less elegant than operator overload
    // but for high performance applications it makes sense

    vector<int> a{{1, 2, 3}};
    vector<int> b{{2, 2, 2}};
    vector<int> c{{7, 6, 5}};

    vector<int> result;
    add3(a, b, c, result);

    std::cout << "Result: ( ";
    for (const auto &i : result.data) {
        std::cout << i << " ";
    }
    std::cout << ")\n";

    return 0;
}