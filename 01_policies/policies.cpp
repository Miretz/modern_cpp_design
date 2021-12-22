#include <iostream>
#include <string>

// various creation policies

template <class T> struct OpNewCreator {
    static T *create() { return new T; }
};

template <class T> struct MallocCreator {
    static T *create() {
        void *buf = std::malloc(sizeof(T));
        if (!buf)
            return 0;
        return new (buf) T;
    }
};

template <class T> struct PrototypeCreator {
    PrototypeCreator(T *pObj = 0) : pPrototype_(pObj) {}
    T *create() { return pPrototype_ ? pPrototype_->clone() : 0; }
    T *getPrototype() { return pPrototype_; }
    void setPrototype(T *pObj) { pPrototype_ = pObj; }

  private:
    T *pPrototype_;
};

// class to construct

class Widget {
  public:
    Widget() = default;
    Widget(std::string str) : greeting_(str){};
    std::string greeting_ = "Hello\n";
    void sayHello() { std::cout << greeting_; }
    Widget *clone() { return new Widget(greeting_); }
};

// using template template parameters to create a creator
template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
    // switch prototype in widget manager
  public:
    void switchPrototype(Widget *pNewPrototype) {
        CreationPolicy<Widget> &myPolicy = *this;
        delete myPolicy.getPrototype();
        myPolicy.setPrototype(pNewPrototype);
    }
};

auto main() -> int {

    // simple class construction
    typedef WidgetManager<OpNewCreator> MyWidgetMgr;
    Widget *w = MyWidgetMgr::create();
    w->sayHello();
    delete w;
    w = nullptr;

    // prototype manager
    typedef WidgetManager<PrototypeCreator> ProtoWidgetMgr;

    ProtoWidgetMgr protoMgr;
    protoMgr.setPrototype(new Widget("Hola\n"));

    Widget *prototypeClone = protoMgr.create();
    prototypeClone->sayHello();

    // use swtich prototype - compile time only works on PrototypeCreator
    protoMgr.switchPrototype(new Widget("Guten tag\n"));

    Widget *prototype2Clone = protoMgr.create();
    prototype2Clone->sayHello();

    delete prototypeClone;
    delete protoMgr.getPrototype();
    delete prototype2Clone;

    prototypeClone = nullptr;
    prototype2Clone = nullptr;

    return 0;
}
