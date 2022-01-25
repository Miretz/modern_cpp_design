#include <iostream>

template <int N> struct fsize_assign {
    template <typename Target, typename Source>
    void operator()(Target &tar, const Source &src) {
        fsize_assign<N - 1>()(tar, src);
        std::cout << "assign entry " << N << '\n';
        tar[N] = src[N];
    }
};

template <> struct fsize_assign<0> {
    template <typename Target, typename Source>
    void operator()(Target &tar, const Source &src) {
        std::cout << "assign entry " << 0 << '\n';
        tar[0] = src[0];
    }
};

template <typename T, int Size> class fsize_vector {
  public:
    const static int my_size = Size;

    typedef fsize_vector self;

    static_assert(my_size > 0, "Vector must be larger than 0.");

    T &operator[](int i) { return data[i]; }
    T operator[](int i) const { return data[i]; }

    self &operator=(const self &that) {
        fsize_assign<my_size - 1>{}(*this, that);
        return *this;
    }

    template <typename Vector> self &operator=(const Vector &that) {
        fsize_assign<my_size - 1>{}(*this, that);
        return *this;
    }

    T data[Size];
};

auto main() -> int {
    fsize_vector<float, 4> v, w;
    v[0] = 1.0;
    v[1] = 1.0;
    v[2] = 2.0;
    v[3] = -3.0;

    w = v;
}