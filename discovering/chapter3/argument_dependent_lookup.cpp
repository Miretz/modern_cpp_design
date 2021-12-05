#include <iostream>

namespace rocketscience {
struct matrix {};
void initialize(matrix &A) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void add(const matrix &A, const matrix &B, matrix &C) {}
matrix operator+(const matrix &A, const matrix &B) {
  matrix C;
  initialize(C);
  add(A, B, C);
  return C;
}

// adl can also select function templates based on namespace
namespace mat {
struct sparse_matrix {};
struct dense_matrix {};
struct uber_matrix {};

template <typename Matrix> double one_norm(const Matrix &A) {
  std::cout << __PRETTY_FUNCTION__ << '\n';
  return 42.1;
}
} // namespace mat

namespace vec {
struct sparse_vector {};
struct dense_vector {};
struct uber_vector {};

template <typename Vector> double one_norm(const Vector &A) {
  std::cout << __PRETTY_FUNCTION__ << '\n';
  return 34.5;
}
} // namespace vec

} // namespace rocketscience

int main() {
  rocketscience::matrix A, B, C, D;
  rocketscience::initialize(B); // qualified
  initialize(C);                // relies on ADL

  // int k = 24;
  //  rocketscience::initialize(k); // error diffeent argument
  //  initialize(k);

  A = B + C + D; // adl also works with operators

  rocketscience::vec::uber_vector uv;
  one_norm(uv);
}
