#ifndef TASK_TWO_HPP
#define TASK_TWO_HPP

#include <iterator>
#include <algorithm>
#include <functional>
#include "statsObject.hpp"

using in_shape = std::istream_iterator<Shape>;
using out_shape = std::ostream_iterator<Shape>;

const auto Comparator = [](const Shape& lhs, const Shape& rhs) -> bool
{
  return lhs.type < rhs.type;
};

void task2(std::istream & sin, std::ostream & os)
{
  Shapes container{ in_shape(sin), in_shape() };

  if (!sin.eof() && sin.fail())
  {
    throw std::invalid_argument("Error while reading data in task2!\n");
  }

  StatsObject shapeStats;
  shapeStats = std::for_each(container.begin(), container.end(), shapeStats);

  container.erase(std::remove_if(container.begin(), container.end(), [](const Shape& shape)
  {
    return shape.vertices.size() == PENTAGON_VERTICES;
  }), container.end());

  std::vector<Point> vertices(container.size());
  std::transform(container.begin(), container.end(), vertices.begin(), [](const Shape& shape)
  {
    return shape.vertices.front();
  });

  std::sort(container.begin(), container.end(), Comparator);

  os << shapeStats;
  os << "Points: ";
  std::copy(vertices.begin(), vertices.end(), std::ostream_iterator<Point>(os, " "));
  os << "\nShapes:\n";
  std::copy(container.begin(), container.end(), out_shape(os, "\n"));
}

#endif
