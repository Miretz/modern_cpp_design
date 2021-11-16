#define _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR 1

#include <iostream>
#include <memory>

#include "../loki-0.1.7/include/loki/Singleton.h"

using std::cout;

using Loki::CreateUsingNew;
using Loki::SingletonHolder;
using Loki::SingletonWithLongevity;

class KeyboardImpl {
public:
  void clack() { cout << "Keyboard clack!\n"; }
};
class DisplayImpl {
public:
  void blink() { cout << "Display blink!\n"; }
};
class LogImpl {
public:
  void log() { cout << "Log log!\n"; }
};

typedef SingletonHolder<KeyboardImpl, CreateUsingNew> Keyboard;
typedef SingletonHolder<DisplayImpl, CreateUsingNew> Display;
typedef SingletonHolder<LogImpl, CreateUsingNew> Log;

auto main() -> int {
  Keyboard::Instance().clack();
  Display::Instance().blink();
  Log::Instance().log();
  return 0;
}
