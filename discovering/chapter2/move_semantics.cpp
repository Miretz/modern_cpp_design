#include <algorithm>
#include <initializer_list>
#include <iostream>

class vector {
public:
  // Constructor
  explicit vector(size_t n)
      : size_{n * 2}, index_{0}, data_{new double[size_]} {}

  // Destructor
  ~vector() { delete[] data_; }

  // Copy Constructor
  vector(const vector &v)
      : size_(v.size_), index_(v.index_), data_(new double[size_]) {
    for (unsigned i = 0; i < index_; ++i) {
      data_[i] = v.data_[i];
    }
  }

  // Initializer List
  explicit vector(std::initializer_list<double> values)
      : size_(values.size() * 2), index_(values.size() - 1),
        data_(new double[size_]) {
    std::copy(begin(values), end(values), data_);
  }

  // Move Constructor
  vector(vector &&v) : size_(v.size_), data_(v.data_), index_(v.index_) {
    delete[] data_;
    data_ = v.data_;
    v.data_ = nullptr;
    v.size_ = 0;
  }


  // Move Assignment
  vector& operator=(vector&& src){
    std::swap(data_, src.data_);
    return *this;
  }

  // Methods
  void push_back(double value) {
    if (index_ < size_) {
      data_[index_] = value;
      index_++;
    }
  }

  double &operator[](size_t pos) { return data_[pos]; }

  void print() const {
    for (size_t i = 0; i < index_; ++i) {
      std::cout << data_[i] << ' ';
    }
    std::cout << '\n';
  }

private:
  size_t size_ = 0;
  size_t index_ = 0;
  double *data_ = nullptr;
};

auto main() -> int {

  vector v1{10, 11, 12};
  v1.push_back(13);
  v1.print();

  auto v2 = std::move(v1); // std::move only casts lvalue to rvalue
  v2[1] = 2;

  // v1.print(); // v1 is UD after move
  v2.print();

  // std::move is almost always a code smell because it leaves the original
  // reference broken

  return 0;
}