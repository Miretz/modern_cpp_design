#include <iostream>
#include <vector>

class NullType {};

template <typename T> class TypeTraits {
  private:
    // pointer detection
    template <class U> struct PointerTraits {
        enum { result = false };
        using PointeeType = NullType;
    };
    template <class U> struct PointerTraits<U *> {
        enum { result = true };
        using PointeeType = U;
    };

  public:
    enum { isPointer = PointerTraits<T>::result };
    using pType = typename PointerTraits<T>::PointeeType;
};

auto main() -> int {
    const bool iterIsPtr = TypeTraits<std::vector<int>::iterator>::isPointer;
    std::cout << "vector<int>::iterator is " << (iterIsPtr ? "fast" : "smart");
    std::cout << '\n';
    return 0;
}
