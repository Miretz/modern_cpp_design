#include <iostream>

using std::cout;

class Window {};
class Controller {};
class ModalDialog {};
class MyController {};
class ButtonArg {};

template <class ButtonArg> class Button {};

template <class Window, class Controller> struct Widget {
    void what_am_I() { cout << "Generic Implementation\n"; };
};

template <> struct Widget<ModalDialog, MyController> {
    void what_am_I() { cout << "Specialized Implementation\n"; };
};

template <class Window> struct Widget<Window, MyController> {
    void what_am_I() { cout << "Partially Specialized Implementation\n"; };
};

template <class ButtonArg> struct Widget<Button<ButtonArg>, MyController> {
    void what_am_I() { cout << "Further specialized Implementation\n"; };
};

auto main() -> int {

    Widget<Window, Controller> generic;
    Widget<ModalDialog, MyController> specialized;
    Widget<Window, MyController> partial;
    Widget<Button<ButtonArg>, MyController> further_specialized;

    generic.what_am_I();
    specialized.what_am_I();
    partial.what_am_I();
    further_specialized.what_am_I();

    return 0;
}
