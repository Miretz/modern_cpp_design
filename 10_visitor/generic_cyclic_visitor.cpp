#include <iostream>

#include "../loki-0.1.7/include/loki/HierarchyGenerators.h"
#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"
#include "../loki-0.1.7/include/loki/Visitor.h"

using Loki::Typelist;
using Loki::Visitor;

// Generic Cyclic Visitor - Cyclic is faster than Acyclic because there is
// no need for dynamic cast

class DocElement;
class Paragraph;
class RasterBitmap;

template <typename R, class TList>
class CyclicVisitor : public Visitor<TList, R> {
public:
  using ReturnType = R;
  template <class Visited> ReturnType Visit(Visited &host) {
    Visitor<Visited, ReturnType> &subObj = *this;
    return subObj.Visit(host);
  }
};

typedef CyclicVisitor<void,
                      LOKI_TYPELIST_3(DocElement, Paragraph, RasterBitmap)>
    MyVisitor;

// clang-format off
#define DEFINE_CYCLIC_VISITABLE(SomeVisitor) \
    virtual SomeVisitor::ReturnType Accept(SomeVisitor& guest) \
    { return guest.Visit(*this); }
// clang-format on

// Usage example

class DocElement {
public:
  DEFINE_CYCLIC_VISITABLE(MyVisitor);
};

class Paragraph : public DocElement {
public:
  DEFINE_CYCLIC_VISITABLE(MyVisitor);
};

class RasterBitmap : public DocElement {
public:
  DEFINE_CYCLIC_VISITABLE(MyVisitor);
};

class MyConcreteVisitor : public MyVisitor {
public:
  void Visit(DocElement &) override { std::cout << "Visit(DocElement&) \n"; }
  void Visit(Paragraph &) override { std::cout << "Visit(Paragraph&) \n"; }
  void Visit(RasterBitmap &) override {
    std::cout << "Visit(RasterBitmap&) \n";
  }
};

auto main() -> int {
  MyConcreteVisitor visitor;
  Paragraph par;
  DocElement *d = &par;
  d->Accept(visitor);

  RasterBitmap bmp;
  bmp.Accept(visitor);
  return 0;
}
