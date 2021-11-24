#include <iostream>
#include <sstream>
#include <vector>

using in_stream = std::istringstream;
using out_stream = std::ostringstream;

enum class DrawingType { Line = 1, Polygon = 2, Circle = 3 };

class Shape {
public:
  virtual void Draw() const = 0;
  virtual void Rotate(double angle) = 0;
  virtual void Zoom(double zoomFactor) = 0;
  virtual void Save(out_stream &outFile) = 0;
  virtual void Read(in_stream &inFile) = 0;
};

class Line : public Shape {
public:
  void Draw() const override {
    std::cout << "Draw: Line ";
    printInfo();
    std::cout << std::endl;
  }
  void Rotate(double angle) override {
    std::cout << "Rotate: Line ";
    printInfo();
    std::cout << " by angle=" << angle << std::endl;
  }
  void Zoom(double zoomFactor) override {
    std::cout << "Zoom: Line ";
    printInfo();
    std::cout << " by factor=" << zoomFactor << std::endl;
  }
  void Save(out_stream &outFile) override {
    outFile << static_cast<int>(DrawingType::Line) << ' ' << x << ' ' << y;
  }
  void Read(in_stream &inFile) override { inFile >> x >> y; }

private:
  void printInfo() const { std::cout << "(x=" << x << ", y=" << y << ") "; }
  int x = 0;
  int y = 0;
};

class Polygon : public Shape {
public:
  void Draw() const override {
    std::cout << "Draw: Polygon ";
    printInfo();
    std::cout << std::endl;
  }
  void Rotate(double angle) override {
    std::cout << "Rotate: Polygon ";
    printInfo();
    std::cout << " by angle=" << angle << std::endl;
  }
  void Zoom(double zoomFactor) override {
    std::cout << "Zoom: Polygon ";
    printInfo();
    std::cout << " by factor=" << zoomFactor << std::endl;
  }
  void Save(out_stream &outFile) override {
    outFile << static_cast<int>(DrawingType::Polygon) << ' ' << x << ' ' << y
            << ' ' << w << ' ' << h;
  }
  void Read(in_stream &inFile) override { inFile >> x >> y >> w >> h; }

private:
  void printInfo() const {
    std::cout << "(x=" << x << ", y=" << y << ", w=" << w << ", h=" << h
              << ") ";
  }
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;
};

class Circle : public Shape {
public:
  void Draw() const override {
    std::cout << "Draw: Circle ";
    printInfo();
    std::cout << std::endl;
  }
  void Rotate(double angle) override {
    std::cout << "Rotate: Circle ";
    printInfo();
    std::cout << " by angle=" << angle << std::endl;
  }
  void Zoom(double zoomFactor) override {
    std::cout << "Zoom: Circle ";
    printInfo();
    std::cout << " by factor=" << zoomFactor << std::endl;
  }
  void Save(out_stream &outFile) override {
    outFile << static_cast<int>(DrawingType::Polygon) << ' ' << x << ' ' << y
            << ' ' << radius;
  }
  void Read(in_stream &inFile) override { inFile >> x >> y >> radius; }

private:
  void printInfo() const {
    std::cout << "(x=" << x << ", y=" << y << ", radius=" << radius << ") ";
  }
  int x = 0;
  int y = 0;
  int radius = 0;
};

class Drawing {
public:
  void Save(out_stream &outFile);
  void Load(in_stream &inFile);
  void Draw() const;
  void RotateAll(double angle);
  void ZoomAll(double zoomFactor);

private:
  std::vector<Shape *> elements_;
};

void Drawing::Save(out_stream &outFile) {
  for (auto &el : elements_) {
    el->Save(outFile);
  }
}

void Drawing::Load(in_stream &inFile) {
  while (inFile) {
    int dt;
    inFile >> dt;
    DrawingType drawingType = static_cast<DrawingType>(dt);

    Shape *pCurrentObject;
    switch (drawingType) {
    case DrawingType::Line:
      pCurrentObject = new Line;
      break;
    case DrawingType::Polygon:
      pCurrentObject = new Polygon;
      break;
    case DrawingType::Circle:
      pCurrentObject = new Circle;
      break;
    default:
      continue;
    }

    pCurrentObject->Read(inFile);
    elements_.push_back(pCurrentObject);
  }
}

void Drawing::Draw() const {
  for (auto &el : elements_) {
    el->Draw();
  }
}

void Drawing::RotateAll(double angle) {
  for (auto &el : elements_) {
    el->Rotate(angle);
  }
}

void Drawing::ZoomAll(double zoomFactor) {
  for (auto &el : elements_) {
    el->Zoom(zoomFactor);
  }
}

auto main() -> int {

  Drawing drawing;

  out_stream data;
  data << "1 12 14\n";
  data << "2 20 40 10 20\n";
  data << "3 10 10 100";
  in_stream iFile{data.str()};

  drawing.Load(iFile);
  drawing.Draw();

  drawing.RotateAll(45.0);
  drawing.ZoomAll(2.1);

  return 0;
}
