#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

class Widget {
  public:
    Widget(int arg, int id) : property_(arg), id_(id) {}
    auto get_property() const -> int { return property_; }
    auto get_id() const -> int { return id_; }

  private:
    int property_;
    int id_;
};

template <typename T> struct Type2Type { using OriginalType = T; };

template <class T, class U>
auto create(const U &arg, Type2Type<T>) -> std::unique_ptr<T> {
    return std::make_unique<T>(arg);
}

template <class U>
auto create(const U &arg, Type2Type<Widget>) -> std::unique_ptr<Widget> {
    return std::make_unique<Widget>(arg, -1);
}

auto main() -> int {
    auto text = create("Hello", Type2Type<std::string>());
    auto widget = create(100, Type2Type<Widget>());

    std::cout << typeid(text).name();
    std::cout << '\n';
    std::cout << *text;
    std::cout << '\n';

    std::cout << typeid(widget).name();
    std::cout << '\n';
    std::cout << "Widget: property=";
    std::cout << widget->get_property();
    std::cout << " id=";
    std::cout << widget->get_id();
    std::cout << '\n';

    return 0;
}
