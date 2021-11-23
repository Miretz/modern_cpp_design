#include <cmath>
#include <iostream>

class complex {
public:
  double r = 0.0;
  double i = 0.0;

  complex() = default;
  complex(double real, double imaginary = 0.0) : r(real), i(imaginary) {}

  complex(const complex &c)
      : r(c.r), i(c.i) {
  } // copy-constructor = the generated one would be better

  auto real() const -> double { return r; }
  auto imaginary() const -> double { return i; }

  friend std::ostream &operator<<(std::ostream &stream, const complex &c) {
    stream << '(' << c.r << ", " << c.i << ')';
    return stream;
  }
};

double inline complex_abs(complex c) {
  return std::sqrt(c.real() * c.real() + c.imaginary() * c.imaginary());
}

auto main() -> int {

  complex z, c;
  z.r = 3.5;
  z.i = 2;
  c.r = 2;
  c.i = -3.5;
  std::cout << "z is " << z << std::endl;
  std::cout << "c is " << c << std::endl;

  std::cout << z.imaginary() << std::endl;

  complex a1;
  complex a2{};
  complex a3(3);
  complex a4(3, 4);

  std::cout << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << std::endl;

  complex b1(a4);
  complex b2{a4};

  std::cout << b1 << ' ' << b2 << std::endl;

  // implicit constructor - to disable this mark the constructor "explicit"
  complex c1 = 3.1;
  std::cout << c1 << std::endl;

  // implicit conversion to complex type here:
  std::cout << "|7| = " << complex_abs(7.0) << std::endl;

  return 0;
}
