#include <iostream>

#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"

using Loki::NullType;
using Loki::Typelist;

class Shape {
public:
  virtual ~Shape() = default;
};
class Rectangle : public Shape {};
class Ellipse : public Shape {};
class Poly : public Shape {};

template <class Executor, class BaseLhs, class TypesLhs,
          class BaseRhs = BaseLhs, class TypesRhs = TypesLhs,
          typename ResultType = void>
class StaticDispatcher {

public:
  static ResultType Go(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    typedef typename TypesLhs::Head Head;
    typedef typename TypesLhs::Tail Tail;

    if (auto p1 = dynamic_cast<Head *>(&lhs)) {
      return StaticDispatcher<Executor, BaseLhs, NullType, BaseRhs,
                              TypesRhs>::DispatchRhs(*p1, rhs, exec);
    } else {
      return StaticDispatcher<Executor, BaseLhs, Tail, BaseRhs, TypesRhs>::Go(
          lhs, rhs, exec);
    }
  }

  template <class SomeLhs>
  static ResultType DispatchRhs(SomeLhs &lhs, BaseRhs &rhs, Executor exec) {
    typedef typename TypesRhs::Head Head;
    typedef typename TypesRhs::Tail Tail;
    if (auto p2 = dynamic_cast<Head *>(&rhs)) {
      return exec.Fire(lhs, *p2);
    } else {
      return StaticDispatcher<Executor, SomeLhs, NullType, BaseRhs,
                              Tail>::DispatchRhs(lhs, rhs, exec);
    }
  }
};

template <class Executor, class BaseLhs, class BaseRhs, class TypesRhs,
          typename ResultType>
class StaticDispatcher<Executor, BaseLhs, NullType, BaseRhs, TypesRhs,
                       ResultType> {
public:
  static void Go(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    exec.OnError(lhs, rhs);
  }
  static void DispatchRhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    exec.OnError(lhs, rhs);
  }
};

template <class Executor, class BaseLhs, class TypesLhs, class BaseRhs,
          typename ResultType>
class StaticDispatcher<Executor, BaseLhs, TypesLhs, BaseRhs, NullType,
                       ResultType> {
public:
  static void Go(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    exec.OnError(lhs, rhs);
  }
  static void DispatchRhs(BaseLhs &lhs, BaseRhs &rhs, Executor &exec) {
    exec.OnError(lhs, rhs);
  }
};

class HatchingExecutor {
public:
  // Various intersection algorithms
  void Fire(Rectangle &, Rectangle &) { std::cout << "Fire: Rect & Rect\n"; }
  void Fire(Rectangle &, Ellipse &) { std::cout << "Fire: Rect & Ellipse\n"; }
  void Fire(Rectangle &, Poly &) { std::cout << "Fire: Rect & Poly\n"; }
  void Fire(Ellipse &, Poly &) { std::cout << "Fire: Ellipse & Poly\n"; }
  void Fire(Ellipse &, Ellipse &) { std::cout << "Fire: Ellipse & Ellipse\n"; }
  void Fire(Poly &, Poly &) { std::cout << "Fire: Poly & Poly\n"; }
  // Error handling routine
  void OnError(Shape &, Shape &) { std::cout << "Error\n"; }
};

auto main() -> int {

  typedef StaticDispatcher<HatchingExecutor, Shape,
                           LOKI_TYPELIST_2(Rectangle, Ellipse)>
      Dispatcher;

  Shape *p1 = new Rectangle;
  Shape *p2 = new Ellipse;

  HatchingExecutor exec;
  Dispatcher::Go(*p1, *p2, exec);

  delete p2;
  delete p1;

  return 0;
}