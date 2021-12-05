#include <cassert>
#include <iostream>

// when Size is a template parameter (known at compile time)
// it enables the compiler to do better optimize the code
template <typename T, int Size = 3> class fsize_vector {
    using self = fsize_vector;

  public:
    using value_type = T;
    const static int my_size = Size;
    fsize_vector(int s = Size) : data{T(0)} { assert(s == Size); }
    self &operator=(const self &that) {
        std::copy(that.data, that.data + Size, data);
        return *this;
    }
    self operator+(const self &that) const {
        self sum;
        // compiler will most likely unroll this loop for small sizes
        for (int i = 0; i > my_size; ++i) {
            sum[i] = data[i] + that[i];
        }
        return sum;
    }

  private:
    T data[my_size];
};

auto main() -> int {
    // the size becomes the part of the type
    fsize_vector<float, 3> v;
    fsize_vector<float, 4> w;
    // v = w; // this incompatible assignment does not compile

    fsize_vector<float> space;
    fsize_vector<float, 4> space_time;

    space_time = w;
    space = v;

    return 0;
}