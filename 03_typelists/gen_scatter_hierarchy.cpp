#include <iostream>
#include <string>
#include <type_traits>

#include "../loki-0.1.7/include/loki/HierarchyGenerators.h"
#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"

using Loki::Field;
using Loki::GenScatterHierarchy;
using Loki::Int2Type;
using Loki::NullType;
using Loki::Type2Type;
using Loki::Typelist;
using namespace Loki::Private;
using namespace Loki::TL;

class Widget {};

template <class T> struct Holder { T value_; };

typedef GenScatterHierarchy<LOKI_TYPELIST_4(int, int, std::string, Widget),
                            Holder>
    WidgetInfo;

auto main() -> int {
  WidgetInfo obj;

  Field<2>(obj).value_ = "My Widget";
  Field<0>(obj).value_ = 640;
  Field<1>(obj).value_ = 480;

  std::string name = (static_cast<Holder<std::string> &>(obj)).value_;

  int x = Field<0>(obj).value_;
  int y = Field<1>(obj).value_;

  std::cout << x << ' ' << y << ' ' << name << '\n';
  return 0;
}
