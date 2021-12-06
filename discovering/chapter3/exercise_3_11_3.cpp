#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>

// I know this is super lazy as I'm just wrapping the std::vector

template <typename T> class Stack {
  public:
    Stack() = default;
    ~Stack() = default;

    T top() const { return stack_.back(); }
    T pop() {
        if (empty()) {
            throw std::range_error("Error: Stack underflow");
        }
        auto top_item = top();
        stack_.pop_back();
        return top_item;
    }
    void push(const T &item) {
        if (full()) {
            throw std::range_error("Error: Stack overflow");
        }
        stack_.push_back(item);
    }
    void clear() { stack_.clear(); }
    size_t size() const { return stack_.size(); }
    bool full() const { return size() == k_max_stack_size; }
    bool empty() const { return stack_.empty(); }

  private:
    // maximal value should be hard-wired
    static constexpr size_t k_max_stack_size = 5;
    std::vector<T> stack_;
};

auto main() -> int {
    Stack<int> s;
    s.push(5);
    s.push(6);
    s.push(7);
    s.push(8);
    s.push(9);
    // s.push(10); // exception

    std::cout << "Stack top: " << s.top() << '\n';
    std::cout << "Stack size: " << s.size() << '\n';
    std::cout << std::boolalpha;
    std::cout << "Stack full: " << s.full() << '\n';
    std::cout << "Stack empty: " << s.empty() << '\n';

    s.pop();
    s.pop();
    s.pop();
    s.pop();
    auto v = s.pop();
    // s.pop(); // exception

    std::cout << "Stack top: " << s.top() << '\n';
    std::cout << "Popped value: " << v << '\n';
    std::cout << "Stack size: " << s.size() << '\n';
    std::cout << "Stack full: " << s.full() << '\n';
    std::cout << "Stack empty: " << s.empty() << '\n';

    s.clear();
    std::cout << "Stack full: " << s.full() << '\n';
    std::cout << "Stack empty: " << s.empty() << '\n';

    return 0;
}