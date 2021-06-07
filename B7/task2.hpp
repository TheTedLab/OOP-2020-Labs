#ifndef TASK_TWO_HPP
#define TASK_TWO_HPP

#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include "figures.hpp"

using in_shape = std::istream_iterator<Shape::ShapePtr>;
using out_shape = std::ostream_iterator<Shape::ShapePtr>;

void printVector(const std::vector<Shape::ShapePtr>& vector, std::ostream& os)
{
  std::copy(vector.begin(), vector.end(), out_shape(os, ""));
}

void task2(std::istream & sin, std::ostream & os)
{
  std::vector<Shape::ShapePtr> shapes{ in_shape(sin), in_shape() };
  if (!sin.eof() && sin.fail())
  {
    throw std::ios::failure("Error while reading in task2!\n");
  }

  os << "Original:\n";
  printVector(shapes, os);

  auto left = std::bind(&Shape::ShapePtr::operator*, std::placeholders::_1);
  auto right = std::bind(&Shape::ShapePtr::operator*, std::placeholders::_2);

  os << "Left-Right:\n";
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft, left, right));
  printVector(shapes, os);

  os << "Right-Left:\n";
  std::reverse(shapes.begin(), shapes.end());
  printVector(shapes, os);

  os << "Top-Bottom:\n";
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isUpper, left, right));
  printVector(shapes, os);

  os << "Bottom-Top:\n";
  std::reverse(shapes.begin(), shapes.end());
  printVector(shapes, os);
}

#endif
