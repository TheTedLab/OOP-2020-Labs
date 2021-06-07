#include "statsObject.hpp"

StatsObject::StatsObject() :
  verticesCount_(0),
  triangleCount_(0),
  squareCount_(0),
  rectangleCount_(0)
{
}

void StatsObject::operator()(Shape& shape)
{
  verticesCount_ += shape.vertices.size();

  switch (shape.type)
  {
  case Shape::ShapeType::TRIANGLE:
    triangleCount_++;
    break;
  case Shape::ShapeType::SQUARE:
    squareCount_++;
    rectangleCount_++;
    break;
  case Shape::ShapeType::RECTANGLE:
    rectangleCount_++;
    break;
  case Shape::ShapeType::PENTAGON:
  case Shape::ShapeType::POLYGON:
    break;
  }
}

std::ostream& operator<<(std::ostream& os, const StatsObject& stats)
{
  os << "Vertices: " << stats.verticesCount_ << '\n'
      << "Triangles: " << stats.triangleCount_ << '\n'
      << "Squares: " << stats.squareCount_ << '\n'
      << "Rectangles: " << stats.rectangleCount_ << '\n';
  return os;
}
