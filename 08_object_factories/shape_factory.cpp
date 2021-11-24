#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using in_stream = std::istringstream;
using out_stream = std::ostringstream;

/*
 * SHAPE CLASSES
 */

class Shape {
public:
  virtual void Draw() const = 0;
  virtual void Rotate(double angle) = 0;
  virtual void Zoom(double zoomFactor) = 0;
  virtual void Save(out_stream &outFile) = 0;
  virtual void Read(in_stream &inFile) = 0;
  virtual ~Shape() = default;
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
  void Save(out_stream &outFile) override { outFile << x << ' ' << y; }
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
    outFile << x << ' ' << y << ' ' << w << ' ' << h;
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
    outFile << x << ' ' << y << ' ' << radius;
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

/*
 *  SHAPE FACTORY
 */

class ShapeFactory {
public:
  typedef Shape *(*CreateShapeCallback)();

private:
  typedef std::map<int, CreateShapeCallback> CallbackMap;

public:
  bool RegisterShape(int ShapeId, CreateShapeCallback CreateFn);
  bool UnregisterShape(int ShapeId);
  Shape *CreateShape(int ShapeId);

private:
  CallbackMap callbacks_;
};

Shape *CreateLine() { return new Line; }
Shape *CreatePolygon() { return new Polygon; }
Shape *CreateCircle() { return new Circle; }

bool ShapeFactory::RegisterShape(int shapeId, CreateShapeCallback createFn) {
  return callbacks_.insert(CallbackMap::value_type(shapeId, createFn)).second;
}

bool ShapeFactory::UnregisterShape(int shapeId) {
  return callbacks_.erase(shapeId) == 1;
}

Shape *ShapeFactory::CreateShape(int shapeId) {
  CallbackMap::const_iterator i = callbacks_.find(shapeId);
  if (i == callbacks_.end()) {
    throw std::runtime_error("Unknown Shape ID");
  }
  return (i->second)();
}

/*
 * DRAWING
 */

class Drawing {
public:
  void Save(out_stream &outFile);
  void Load(in_stream &inFile);
  void Draw() const;
  void RotateAll(double angle);
  void ZoomAll(double zoomFactor);
  ~Drawing() {
    for (std::vector<Shape *>::iterator i = elements_.begin();
         i != elements_.end(); ++i) {
      delete *i;
    }
    elements_.clear();
  }

private:
  std::vector<Shape *> elements_;
};

void Drawing::Save(out_stream &outFile) {
  for (auto &el : elements_) {
    el->Save(outFile);
  }
}

void Drawing::Load(in_stream &inFile) {

  ShapeFactory factory;
  factory.RegisterShape(1, CreateLine);
  factory.RegisterShape(2, CreatePolygon);
  factory.RegisterShape(3, CreateCircle);

  while (inFile) {
    int dt;
    inFile >> dt;
    Shape *pCurrentObject = factory.CreateShape(dt);
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
