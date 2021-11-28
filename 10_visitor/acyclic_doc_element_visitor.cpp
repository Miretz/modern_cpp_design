#include <iostream>
#include <memory>
#include <vector>

static constexpr auto kDefaultFontSize = 10;
static constexpr auto kDefaultNumChars = 42;
static constexpr auto kDefaultNumWords = 61;

class DocElementVisitor {
public:
  DocElementVisitor() = default;
  DocElementVisitor(const DocElementVisitor &) = delete;
  DocElementVisitor(const DocElementVisitor &&) = delete;
  auto operator=(DocElementVisitor &) -> DocElementVisitor & = delete;
  auto operator=(DocElementVisitor &&) -> DocElementVisitor & = delete;
  virtual ~DocElementVisitor() = default;
};

class DocElement {
public:
  // bouncing virtual function
  virtual void Accept(DocElementVisitor &) = 0;
};

/*
PARAGRAPH
*/

class ParagraphVisitor {
public:
  virtual void VisitParagraph(DocElement &) = 0;
};

class Paragraph : public DocElement {
  int fontSize_ = kDefaultFontSize;

public:
  void Accept(DocElementVisitor &v) override {
    if (auto *p = dynamic_cast<ParagraphVisitor *>(&v)) {
      p->VisitParagraph(*this);
    }
  }
  auto NumChars() -> int { return kDefaultNumChars; }
  auto NumWords() -> int { return kDefaultNumWords; }
  auto GetFontSize() const -> int { return fontSize_; }
  void SetFontSize(int value) { fontSize_ = value; }
};

/*
RASTER
*/

class RasterVisitor {
public:
  virtual void VisitRaster(DocElement &) = 0;
};

class RasterBitmap : public DocElement {
public:
  void Accept(DocElementVisitor &v) override {
    if (auto *p = dynamic_cast<RasterVisitor *>(&v)) {
      p->VisitRaster(*this);
    }
  }
};

/*
DOC STATS
*/

class DocStats : public DocElementVisitor,
                 public ParagraphVisitor,
                 public RasterVisitor {
public:
  void VisitParagraph(DocElement &obj) override {
    auto *par = dynamic_cast<Paragraph *>(&obj);
    chars_ += par->NumChars();
    words_ += par->NumWords();
  }
  void VisitRaster(DocElement &) override { ++images_; }

  void Display() {
    std::cout << "Chars: " << chars_ << "\nWords: " << words_
              << "\nImages: " << images_ << '\n';
  }

private:
  int chars_ = 0;
  int words_ = 0;
  int images_ = 0;
};

/*
INCREMENT FONT SIZE
*/

// Use the visitor to add new functionalities
class IncrementFontSize : public DocElementVisitor, public ParagraphVisitor {
public:
  void VisitParagraph(DocElement &obj) override {
    auto *par = dynamic_cast<Paragraph *>(&obj);
    par->SetFontSize(par->GetFontSize() + 1);
  }
};

auto main() -> int {

  DocStats stats;

  auto b1 = std::shared_ptr<RasterBitmap>(new RasterBitmap);
  auto b2 = std::shared_ptr<RasterBitmap>(new RasterBitmap);
  auto p = std::shared_ptr<Paragraph>(new Paragraph);

  std::vector<std::shared_ptr<DocElement>> elements{b1, b2, p};

  for (auto &elem : elements) {
    elem->Accept(stats);
  }

  stats.Display();

  IncrementFontSize incrementFontSize;
  p->Accept(incrementFontSize);
  std::cout << "Visitor incremented font size to: " << p->GetFontSize() << '\n';

  return 0;
}