#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include "point.hpp"

const size_t MIN_VERTICES = 3;
const size_t TRIANGLE_VERTICES = 3;
const size_t QUADRANGLE_VERTICES = 4;
const size_t PENTAGON_VERTICES = 5;

struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    POLYGON
  };

  ShapeType type;
  std::vector<Point> vertices;
};

using Shapes = std::vector<Shape>;

std::istream& operator>>(std::istream& in, Shape & shape);
std::ostream& operator<<(std::ostream& os, const Shape & shape);

bool isTriangle(const Shape & shape);
bool isSquare(const Shape & shape);
bool isRectangle(const Shape & shape);

double getDistance(const Point & first, const Point & second);

#endif
