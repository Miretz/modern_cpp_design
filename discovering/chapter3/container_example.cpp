#include <iostream>
#include <memory>
#include <stdexcept>

struct row_major {}; // just for tagging
struct col_major {};
struct heap {};
struct stack {};

// defaulting
template <typename T = double, typename Orientation = col_major,
          typename where = heap>
class vector {
  public:
    explicit vector(int size = 5) : size_(size), data_(new T[size_]) {}
    vector(const vector &that) : size_(that.size_), data_(new T[size_]) {
        std::copy(&that.data_[0], &that.data[that.size_], &data_[0]);
    }
    int size() const { return size_; };
    const T &operator[](int i) const {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[i];
    }

  private:
    int size_;
    std::unique_ptr<T[]> data_;
};

// defaulting based on preceding parameters
template <typename T, typename U = T> class pair {};

auto main() -> int {
    vector<float, row_major, heap> v(5);
    vector<float, col_major, stack> w(4);
    vector<> y; // defaulted

    pair<int, float> p1;
    pair<int> p2;

    return 0;
}