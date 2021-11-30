#include <iostream>

#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"

using Loki::NullType;
using Loki::Typelist;
using namespace Loki::TL;

class Shape {
public:
  virtual ~Shape() = default;
};
class Rectangle : public Shape {};
class Ellipse : public Shape {};
class Poly : public Shape {};

template <class Executor, bool symmetric, class BaseLhs, class TypesLhs,
          class BaseRhs = BaseLhs, class TypesRhs = TypesLhs,
          typename ResultType = void>
class StaticDispatcher {

  template <bool swapArgs, class SomeLhs, class SomeRhs>
  struct InvocationTraits {
    static void DoDispatch(SomeLhs &lhs, SomeRhs &rhs, Executor &exec) {
      exec.Fire(lhs, rhs);
    }
  };

  template <class SomeLhs, class SomeRhs>
  struct InvocationTraits<true, SomeLhs, SomeRhs> {
    static void DoDispatch(SomeLhs &lhs, SomeRhs &rhs, Executor &exec) {
      exec.Fire(rhs, lhs); // swap arguments
    }
  };

public:
  static void DispatchRhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    typedef typename TypesLhs::Head Head;
    typedef typename TypesLhs::Tail Tail;
    if (auto p2 = dynamic_cast<Head *>(&rhs)) {
      enum {
        swapArgs = symmetric && int(IndexOf<TypesRhs, Head>::value) <
                                    int(IndexOf<TypesLhs, BaseLhs>::value)
      };
      typedef InvocationTraits<swapArgs, BaseLhs, Head> CallTraits;
      return CallTraits::DoDispatch(lhs, *p2, exec);
    } else {
      return DispatchRhs(lhs, rhs, exec);
    }
  }

  static ResultType Go(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    typedef typename TypesLhs::Head Head;
    typedef typename TypesLhs::Tail Tail;

    if (auto p1 = dynamic_cast<Head *>(&lhs)) {
      return StaticDispatcher<Executor, symmetric, Head, Tail, BaseRhs,
                              TypesRhs>::DispatchRhs(*p1, rhs, exec);
    } else {
      return StaticDispatcher<Executor, symmetric, BaseLhs, NullType, BaseRhs,
                              TypesRhs>::Go(lhs, rhs, exec);
    }
  }
};

template <class Executor, bool sym, class BaseLhs, class BaseRhs,
          class TypesRhs, typename ResultType>
class StaticDispatcher<Executor, sym, BaseLhs, NullType, BaseRhs, TypesRhs,
                       ResultType> {
public:
  static void Go(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {}
  static void DispatchRhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    exec.OnError(lhs, rhs);
  }
};

template <class Executor, bool sym, class BaseLhs, class TypesLhs,
          class BaseRhs, typename ResultType>
class StaticDispatcher<Executor, sym, BaseLhs, TypesLhs, BaseRhs, NullType,
                       ResultType> {
public:
  static void DispatchRhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec) {
    exec.OnError(lhs, rhs);
  }
};

class HatchingExecutor {
public:
  // Various intersection algorithms
  void Fire(Shape &, Ellipse &) { std::cout << "Fire: Rect & Rect\n"; }
  void Fire(Shape &, Rectangle &) { std::cout << "Fire: Rect & Rect\n"; }
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

  typedef StaticDispatcher<HatchingExecutor, true, Shape,
                           LOKI_TYPELIST_3(Rectangle, Ellipse, Poly)>
      Dispatcher;

  Shape *s1 = new Rectangle;
  Shape *s2 = new Ellipse;

  HatchingExecutor exec;

  Dispatcher::Go(*s1, *s2, exec);

  delete s1;
  delete s2;

  return 0;
}