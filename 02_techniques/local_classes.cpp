#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Interface {
  public:
    virtual void fun() = 0;
    Interface() = default;
    virtual ~Interface() = default;

    Interface(Interface &) = delete;
    Interface(Interface &&) = delete;
    auto operator=(Interface &) -> Interface & = delete;
    auto operator=(Interface &&) -> Interface & = delete;
};

template <class T, class P>
auto make_adapter(const T &obj, const P &arg) -> std::unique_ptr<Interface> {
    class Local : public Interface {
      public:
        Local(const T &obj, P arg) : obj_(obj), arg_(std::move(arg)) {}
        void fun() override { obj_.call(arg_); }

      private:
        T obj_;
        P arg_;
    };
    return std::make_unique<Local>(obj, arg);
};

class Test {
  public:
    void call(const std::string &i) { std::cout << i; }
};

auto main() -> int {

    constexpr Test original;
    constexpr auto text = "Foo\n";

    auto i = make_adapter<Test, std::string>(original, text);
    i->fun();

    return 0;
}
