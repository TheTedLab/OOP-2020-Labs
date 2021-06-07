#include <string>
#include <stdexcept>
#include "shape.hpp"
#include "figures.hpp"
#include "utils.hpp"

Shape::Shape(const Point & core) :
  core_(core)
{}

bool Shape::isMoreLeft(const Shape & shape) const
{
  return core_.x < shape.core_.x;
}

bool Shape::isUpper(const Shape & shape) const
{
  return core_.y > shape.core_.y;
}

std::ostream& operator<<(std::ostream& os, const Shape::ShapePtr& shape)
{
  shape->draw(os);
  return os;
}

std::istream& operator>>(std::istream& sin, Shape::ShapePtr& shape)
{
  std::string name;
  sin >> std::ws;

  if (sin.peek() == EOF)
  {
    sin.setstate(std::ios::failbit);
    return sin;
  }

  while (sin.peek() != '(' && !std::isblank(sin.peek()))
  {
    if (sin.peek() == '\n')
    {
      sin.setstate(std::ios::failbit);
      break;
    }
    else
    {
      name += sin.get();
    }
  }

  if (sin.fail())
  {
    return sin;
  }

  Point point;
  sin >> point;

  try
  {
    shape = shapeParser(name, point);
  }
  catch(std::invalid_argument&)
  {
    sin.setstate(std::ios::failbit);
  }
  return sin;
}

Shape::ShapePtr shapeParser(const std::string& name, const Point& core)
{
  if (name == "CIRCLE")
  {
    return std::make_shared<const Circle>(core);
  }
  else if (name == "SQUARE")
  {
    return std::make_shared<const Square>(core);
  }
  else if (name == "TRIANGLE")
  {
    return std::make_shared<const Triangle>(core);
  }
  else
  {
    throw std::invalid_argument("Invalid figure name format!\n");
  }
}
