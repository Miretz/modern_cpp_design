#include <iostream>
#include <memory>
#include <string_view>

class Interface {
public:
  virtual void fun() = 0;
  virtual ~Interface() = default;
};

template <class T, class P>
std::unique_ptr<Interface> make_adapter(const T &obj, const P &arg) {
  class Local : public Interface {
  public:
    Local(const T &obj, const P &arg) : obj_(obj), arg_(arg) {}
    virtual void fun() { obj_.call(arg_); }

  private:
    T obj_;
    P arg_;
  };
  return std::make_unique<Local>(obj, arg);
};

class Test {
public:
  void call(std::string_view i) { std::cout << i; }
};

auto main() -> int {

  constexpr Test original;
  constexpr std::string_view text = "Foo\n";

  auto i = make_adapter<Test, std::string_view>(original, text);
  i->fun();

  return 0;
}
