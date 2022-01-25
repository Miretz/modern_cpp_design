#include <iostream>

template <typename Matrix, typename Vector> struct mat_vec_et {
    const static int my_rows = Matrix::my_rows, my_cols = Matrix::my_cols;
    mat_vec_et(const Matrix &A, const Vector &v) : A(A), v(v) {}
    const Matrix &A;
    const Vector &v;
};

template <int Rows, int Cols> struct fsize_mat_vec_mult {
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix &A, const VecIn &v_in, VecOut &v_out) {
        fsize_mat_vec_mult<Rows, Cols - 1>()(A, v_in, v_out);
        v_out[Rows] += A[Rows][Cols] * v_in[Cols];
    }
};

template <int Rows> struct fsize_mat_vec_mult<Rows, 0> {
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix &A, const VecIn &v_in, VecOut &v_out) {
        fsize_mat_vec_mult<Rows - 1, Matrix::my_cols - 1>()(A, v_in, v_out);
        v_out[Rows] = A[Rows][0] * v_in[0];
    }
};

template <> struct fsize_mat_vec_mult<0, 0> {
    template <typename Matrix, typename VecIn, typename VecOut>
    void operator()(const Matrix &A, const VecIn &v_in, VecOut &v_out) {
        v_out[0] = A[0][0] * v_in[0];
    }
};

template <typename T, int Size> struct fsize_vector {

    const static int my_size = Size;
    static_assert(my_size > 0, "Vector must be larger than 0.");

    T &operator[](int i) { return data[i]; }
    T operator[](int i) const { return data[i]; }

    int size() const { return my_size; }

    using self = fsize_vector;
    template <typename Matrix, typename Vector>
    self &operator=(const mat_vec_et<Matrix, Vector> &that) {
        using et = mat_vec_et<Matrix, Vector>;
        using mv = fsize_mat_vec_mult<et::my_rows - 1, et::my_cols - 1>;
        mv{}(that.A, that.v, *this);
        return *this;
    }

    T data[Size];
};

template <typename T, int Rows, int Cols> struct fsize_matrix {
    static_assert(Rows > 0, "Rows must be larger than 0.");
    static_assert(Cols > 0, "Cols must be larger than 0.");

    using self = fsize_matrix;
    using value_type = T;

    const static int my_rows = Rows, my_cols = Cols;

    const T *operator[](int r) const { return data[r]; }
    T *operator[](int r) { return data[r]; }

    mat_vec_et<self, fsize_vector<T, Cols>>
    operator*(const fsize_vector<T, Cols> &v) const {
        return {*this, v};
    }

    T data[Rows][Cols];
};

template <typename T, int Size>
std::ostream &operator<<(std::ostream &os, const fsize_vector<T, Size> &v) {
    os << '[';
    for (int i = 0; i < v.size(); ++i)
        os << v[i] << ',';
    os << ']';
    return os;
}

auto main() -> int {
    fsize_vector<float, 4> v, w;
    v[0] = 1.0;
    v[1] = 1.0;
    v[2] = 2.0;
    v[3] = -3.0;

    fsize_matrix<float, 4, 4> A;

    A[0][1] = 2.3;
    A[1][2] = 3.4;
    A[2][3] = 4.1;
    A[3][0] = 5.;

    w = A * v;
    std::cout << "A * v = " << w << '\n';

    return 0;
}