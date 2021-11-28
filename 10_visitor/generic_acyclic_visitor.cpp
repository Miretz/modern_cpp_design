#include <iostream>

// Generic Acyclic Visitor

class BaseVisitor {
public:
  BaseVisitor() = default;
  BaseVisitor(const BaseVisitor &) = delete;
  BaseVisitor(const BaseVisitor &&) = delete;
  auto operator=(const BaseVisitor &) = delete;
  auto operator=(const BaseVisitor &&) = delete;
  virtual ~BaseVisitor() = default;
};

// clang-format off
#define DEFINE_VISITABLE() \
  virtual ReturnType Accept(BaseVisitor& guest) \
  { return AcceptImpl(*this, guest); }
// clang-format on

template <class T, typename R = void> class Visitor {
public:
  using ReturnType = R;
  virtual auto Visit(T &) -> ReturnType = 0;
};

template <typename R = void> class BaseVisitable {
public:
  using ReturnType = R;

  BaseVisitable() = default;
  BaseVisitable(const BaseVisitable &) = delete;
  BaseVisitable(const BaseVisitable &&) = delete;
  auto operator=(const BaseVisitable &) = delete;
  auto operator=(const BaseVisitable &&) = delete;

  virtual ~BaseVisitable() = default;
  virtual auto Accept(BaseVisitor &) -> ReturnType = 0;

protected:
  template <class T>
  static auto AcceptImpl(T &visited, BaseVisitor &guest) -> ReturnType {
    if (auto *p = dynamic_cast<Visitor<T> *>(&guest)) {
      return p->Visit(visited);
    }
    return ReturnType();
  }
};

// Usage example

class DocElement : public BaseVisitable<> {
public:
  DEFINE_VISITABLE()
};

class Paragraph : public DocElement {
public:
  DEFINE_VISITABLE();
};

class MyConcreteVisitor : public BaseVisitor,
                          public Visitor<DocElement>,
                          public Visitor<Paragraph> {
public:
  void Visit(DocElement &) override { std::cout << "Visit(DocElement&) \n"; }
  void Visit(Paragraph &) override { std::cout << "Visit(Paragraph&) \n"; }
};

auto main() -> int {
  MyConcreteVisitor visitor;
  Paragraph par;
  DocElement *d = &par;
  d->Accept(visitor);
  return 0;
}
