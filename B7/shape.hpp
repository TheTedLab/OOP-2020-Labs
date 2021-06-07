#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "point.hpp"

class Shape
{
public:
  using ShapePtr = std::shared_ptr<const Shape>;
  Shape(const Point & core);
  virtual ~Shape() = default;
  virtual void draw(std::ostream& os) const = 0;
  bool isMoreLeft(const Shape & shape) const;
  bool isUpper(const Shape & shape) const;
protected:
  Point core_;
};

std::ostream& operator<<(std::ostream& os, const Shape::ShapePtr& shape);
std::istream& operator>>(std::istream& sin, Shape::ShapePtr& shape);
Shape::ShapePtr shapeParser(const std::string& name, const Point& core);

#endif
