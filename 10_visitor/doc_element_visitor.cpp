#include <iostream>
#include <memory>
#include <vector>

class Paragraph;
class RasterBitmap;

class DocElementVisitor {
public:
  virtual void VisitParagraph(Paragraph &) = 0;
  virtual void VisitRasterBitmap(RasterBitmap &) = 0;
};

class DocElement {
public:
  // bouncing virtual function
  virtual void Accept(DocElementVisitor &) = 0;
};

class Paragraph : public DocElement {
public:
  void Accept(DocElementVisitor &v) override { v.VisitParagraph(*this); }
  int NumChars() { return 42; }
  int NumWords() { return 61; }
};

class RasterBitmap : public DocElement {
public:
  void Accept(DocElementVisitor &v) override { v.VisitRasterBitmap(*this); }
};

class DocStats : public DocElementVisitor {
public:
  virtual void VisitParagraph(Paragraph &par) override {
    chars_ += par.NumChars();
    words_ += par.NumWords();
  }
  virtual void VisitRasterBitmap(RasterBitmap &) override { ++images_; }

  void Display() {
    std::cout << "Chars: " << chars_ << "\nWords: " << words_
              << "\nImages: " << images_ << '\n';
  }

private:
  int chars_ = 0;
  int words_ = 0;
  int images_ = 0;
};

auto main() -> int {

  DocStats stats;

  auto b1 = std::shared_ptr<DocElement>(new RasterBitmap);
  auto b2 = std::shared_ptr<DocElement>(new RasterBitmap);
  auto p = std::shared_ptr<DocElement>(new Paragraph);

  std::vector<std::shared_ptr<DocElement>> elements{b1, b2, p};

  for (auto &elem : elements) {
    elem->Accept(stats);
  }

  stats.Display();

  return 0;
}