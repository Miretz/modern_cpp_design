#include <iostream>
#include <memory>
#include <string>
#include <utility>

// various creation policies

template <class T> struct OpNewCreator {
    static auto create() -> std::unique_ptr<T> { return std::make_unique<T>(); }
};

template <class T> struct PrototypeCreator {
    PrototypeCreator() = default;
    explicit PrototypeCreator(std::unique_ptr<T> pObj) : pPrototype_(pObj) {}
    auto create() -> std::unique_ptr<T> {
        return pPrototype_ ? pPrototype_->clone() : nullptr;
    }
    auto getPrototype() -> std::unique_ptr<T> { return pPrototype_; }
    void setPrototype(std::unique_ptr<T> prototype) {
        pPrototype_ = std::move(prototype);
    }

  private:
    std::unique_ptr<T> pPrototype_;
};

// class to construct

class Widget {
  public:
    Widget() = default;
    explicit Widget(std::string str) : greeting_(std::move(str)){};

    void sayHello() { std::cout << greeting_; }
    auto clone() -> std::unique_ptr<Widget> {
        return std::make_unique<Widget>(greeting_);
    }

    std::string greeting_ = "Hello\n";
};

// using template template parameters to create a creator
template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
    // switch prototype in widget manager
  public:
    void switchPrototype(std::unique_ptr<Widget> prototype) {
        CreationPolicy<Widget> &myPolicy = *this;
        myPolicy.setPrototype(std::move(prototype));
    }
};

auto main() -> int {

    // simple class construction
    using MyWidgetMgr = WidgetManager<OpNewCreator>;
    auto w = MyWidgetMgr::create();
    w->sayHello();

    // prototype manager
    using ProtoWidgetMgr = WidgetManager<PrototypeCreator>;

    ProtoWidgetMgr protoMgr;
    protoMgr.setPrototype(std::make_unique<Widget>("Hola\n"));

    auto prototypeClone = protoMgr.create();
    prototypeClone->sayHello();

    // use swtich prototype - compile time only works on PrototypeCreator
    protoMgr.switchPrototype(std::make_unique<Widget>("Guten tag\n"));

    auto prototype2Clone = protoMgr.create();
    prototype2Clone->sayHello();

    return 0;
}
