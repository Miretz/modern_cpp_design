#include <iostream>
#include <vector>

class Polynomial {

public:
  explicit Polynomial(size_t degree) : degree_(degree) {
    data_.resize(degree_);
  }

  ~Polynomial() = default;

  Polynomial(Polynomial &) = default;

  // 2.8.3
  Polynomial(std::initializer_list<double> values) : degree_(values.size()) {
    std::cout << "Initializer list construction used!\n";
    data_.resize(degree_);
    std::copy(begin(values), end(values), begin(data_));
  }

  Polynomial &operator=(std::initializer_list<double> values) {
    std::cout << "Initializer assignment operator used!\n";
    data_.resize(degree_);
    std::copy(std::begin(values), std::end(values), std::begin(data_));
    return *this;
  }
  // end of 2.8.3

  Polynomial(Polynomial &&src)
      : degree_(std::move(src.degree_)), data_(std::move(src.data_)) {
    std::cout << "Move constructor used!\n";
  }

  Polynomial &operator=(Polynomial &&src) {
    std::cout << "Move assignment operator used!\n";
    data_ = std::move(src.data_);
    degree_ = std::move(src.degree_);
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Polynomial &p) {
    stream << '[';
    std::string delim = "";
    for (const auto &item : p.data_) {
      stream << delim << item;
      delim = ", ";
    }
    stream << ']';
    return stream;
  }

private:
  size_t degree_;
  std::vector<double> data_;
};

// 2.8.2
Polynomial f(double c2, double c1, double c0) {
  Polynomial p{c2, c1, c0};
  // explicit std::move to disable the return value optimization / copy ellision
  // and print the message
  return std::move(p);

  // ideally it should be just - the compiler optimizes this via RVO / copy
  // ellision: return p;
}

auto main() -> int {
  auto res = f(3.2, 3.1, 8.0);
  std::cout << res << std::endl;

  Polynomial res2 = {1, 2, 3};
  std::cout << res2 << std::endl;

  return 0;
}