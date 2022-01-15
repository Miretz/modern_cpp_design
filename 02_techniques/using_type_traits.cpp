#include <iostream>

#include "../loki-0.1.7/include/loki/TypeTraits.h"

using Loki::TypeTraits;

enum CopyAlgoSelector { Conservative, Fast };

// Int2Type - for the example
template <int v> struct Int2Type {
    enum { value = v };
};

// Fake BitBlast for the example
template <typename InIt, typename OutIt>
void BitBlast(InIt first, OutIt result, int size) {
    std::cout << "BitBlast called\n";
    memcpy(result, first, size);
}

// conservative routine - works for any type
template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Conservative>) {
    std::cout << "Conservative version called\n";
    for (; first != last; ++first, ++result) {
        *result = *first;
    }
    return result;
};

// fast routine - works only for pointers to raw data
template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Fast>) {
    const size_t n = last - first;
    BitBlast(first, result, n * sizeof(*first));
    return result + n;
};

template <typename InIt, typename OutIt>
OutIt Copy(InIt first, InIt last, OutIt result) {
    typedef typename TypeTraits<InIt>::PointeeType SrcPointee;
    typedef typename TypeTraits<OutIt>::PointeeType DestPointee;
    enum {
        copyAlgo = TypeTraits<InIt>::isPointer &&
                           TypeTraits<OutIt>::isPointer &&
                           TypeTraits<SrcPointee>::isStdFundamental &&
                           TypeTraits<DestPointee>::isStdFundamental &&
                           sizeof(SrcPointee) == sizeof(DestPointee)
                       ? Fast
                       : Conservative
    };
    return CopyImpl(first, last, result, Int2Type<copyAlgo>());
}

auto main() -> int {

    int my_array[] = {1, 5, 6, 8, 9};

    int *p1 = &my_array[0];
    int *p2 = &my_array[4];

    unsigned int result_array[4];

    unsigned int *p3 = &result_array[0];
    Copy(p1, p2, p3);

    // print something
    std::cout << result_array[3] << '\n';

    return 0;
}
