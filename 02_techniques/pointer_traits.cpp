#include <iostream>
#include <vector>

class NullType {};

template <typename T> class TypeTraits {
private:
  // pointer detection
  template <class U> struct PointerTraits {
    enum { result = false };
    typedef NullType PointeeType;
  };
  template <class U> struct PointerTraits<U *> {
    enum { result = true };
    typedef U PointeeType;
  };

public:
  enum { isPointer = PointerTraits<T>::result };
  typedef typename PointerTraits<T>::PointeeType pType;
};

auto main() -> int {

  const bool iterIsPtr = TypeTraits<std::vector<int>::iterator>::isPointer;
  std::cout << "vector<int>::iterator is " << (iterIsPtr ? "fast" : "smart");
  std::cout << '\n';
  return 0;
}
