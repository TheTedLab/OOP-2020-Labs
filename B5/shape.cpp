#include "shape.hpp"
#include <cmath>
#include <iterator>
#include <algorithm>

std::istream& operator>>(std::istream& in, Shape& shape)
{
  size_t vertices;
  in >> std::ws >> vertices;

  if (in.peek() == EOF)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  if (vertices < MIN_VERTICES)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), vertices, std::back_inserter(temp));
  shape.vertices.swap(temp);

  switch (shape.vertices.size())
  {
  case TRIANGLE_VERTICES:
    if (isTriangle(shape)) 
    {
      shape.type = Shape::ShapeType::TRIANGLE;
    }
    break;
  case QUADRANGLE_VERTICES:
    if (isSquare(shape))
    {
      shape.type = Shape::ShapeType::SQUARE;
    }
    else if (isRectangle(shape))
    {
      shape.type = Shape::ShapeType::RECTANGLE;
    }
    break;
  case PENTAGON_VERTICES:
    shape.type = Shape::ShapeType::PENTAGON;
    break;
  default:
    shape.type = Shape::ShapeType::POLYGON;
    break;
  }
  return in;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
  os << shape.vertices.size() << ' ';
  std::copy(shape.vertices.begin(), shape.vertices.end(), std::ostream_iterator<Point>(os, " "));
  return os;
}

bool isTriangle(const Shape& shape)
{
  return (shape.vertices.size() == 3);
}

bool isSquare(const Shape& shape)
{
  if (shape.vertices.size() != QUADRANGLE_VERTICES)
  {
    return false;
  }

  double squareAB = getDistance(shape.vertices[0], shape.vertices[1]);
  double squareBC = getDistance(shape.vertices[1], shape.vertices[2]);
  double squareCD = getDistance(shape.vertices[2], shape.vertices[3]);
  double squareDA = getDistance(shape.vertices[3], shape.vertices[0]);

  return ((squareAB == squareBC) && (squareAB == squareCD) && (squareAB == squareDA));
}

bool isRectangle(const Shape& shape)
{
  if (shape.vertices.size() != QUADRANGLE_VERTICES)
  {
    return false;
  }

  double rectAB = getDistance(shape.vertices[0], shape.vertices[1]);
  double rectBC = getDistance(shape.vertices[1], shape.vertices[2]);
  double rectCD = getDistance(shape.vertices[2], shape.vertices[3]);
  double rectDA = getDistance(shape.vertices[3], shape.vertices[0]);
  double diagAC = getDistance(shape.vertices[0], shape.vertices[2]);
  double diagBD = getDistance(shape.vertices[1], shape.vertices[3]);

  return ((rectAB == rectCD) && (rectBC == rectDA) && (diagAC == diagBD));
}

double getDistance(const Point& first, const Point& second)
{
  return sqrt(pow((second.x - first.x), 2) + pow((second.y - first.y), 2));
}
