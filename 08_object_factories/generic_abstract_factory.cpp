#include <iostream>
#include <type_traits>

#include "../loki-0.1.7/include/loki/HierarchyGenerators.h"
#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"

#include "monsters.h"

using Loki::GenLinearHierarchy;
using Loki::GenScatterHierarchy;
using Loki::Type2Type;
using Loki::Typelist;

using namespace Loki::Private;
using namespace Loki::TL;

template <class T> class AbstractFactoryUnit {
public:
  virtual T *DoCreate(Type2Type<T>) = 0;
  virtual ~AbstractFactoryUnit() {}
};

template <class TList, template <class> class Unit = AbstractFactoryUnit>
class AbstractFactory : public GenScatterHierarchy<TList, Unit> {
public:
  typedef TList ProductList;
  template <class T> T *Create() {
    Unit<T> &unit = *this;
    return unit.DoCreate(Type2Type<T>());
  }
};

typedef AbstractFactory<LOKI_TYPELIST_3(Soldier, Monster, SuperMonster)>
    AbstractEnemyFactory;

template <class ConcreteProduct, class Base>
class OpNewFactoryUnit : public Base {
  typedef typename Base::ProductList BaseProductList;

protected:
  typedef typename BaseProductList::Tail ProductList;

public:
  typedef typename BaseProductList::Head AbstractProduct;
  ConcreteProduct *DoCreate(Type2Type<AbstractProduct>) {
    return new ConcreteProduct;
  }
};

template <class AbstractFact,
          template <class, class> class Creator = OpNewFactoryUnit,
          class TList = typename AbstractFact::ProductList>
class ConcreteFactory
    : public GenLinearHierarchy<typename Reverse<TList>::Result, Creator,
                                AbstractFact> {
public:
  typedef typename AbstractFact::ProductList ProductList;
  typedef TList ConcreteProductList;
};

typedef ConcreteFactory<AbstractEnemyFactory, OpNewFactoryUnit,
                        LOKI_TYPELIST_3(SillySoldier, SillyMonster,
                                        SillySuperMonster)>
    EasyLevelEnemyFactory;

int main() {
  AbstractEnemyFactory *p = new EasyLevelEnemyFactory;
  Monster *pOgre = p->Create<Monster>();
  pOgre->Growl();

  delete pOgre;
  pOgre = nullptr;
  delete p;
  p = nullptr;

  return 0;
}
